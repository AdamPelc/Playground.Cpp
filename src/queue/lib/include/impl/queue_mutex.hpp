#include <mutex>
#include <deque>
#include <optional>
#include <shared_mutex>
#include <stdexcept>
#include <stdexcept>

namespace impl
{

template<typename type_T, typename container_T = std::deque<type_T>>
class queue_mutex_t
{
public:
    explicit queue_mutex_t(std::size_t capacity);

    [[nodiscard]]
    auto try_dequeue() -> std::optional<type_T>;
    auto enqueue(type_T value) -> void;
    [[nodiscard]]
    auto is_empty() const -> bool;

private:
    mutable std::shared_mutex m_mutex;
    container_T m_container;
};

template<typename type_T, typename container_T>
queue_mutex_t<type_T, container_T>::queue_mutex_t(std::size_t) {}

template<typename type_T, typename container_T>
std::optional<type_T> queue_mutex_t<type_T, container_T>::try_dequeue()
{
    if (is_empty()) {
        return {};
    }

    std::unique_lock lock(m_mutex);
    const auto value = m_container.front();
    m_container.pop_front();
    return value;
}

template<typename type_T, typename container_T>
auto queue_mutex_t<type_T, container_T>::enqueue(type_T value) -> void {
    std::unique_lock lock(m_mutex);
    m_container.push_back(value);
}

template<typename type_T, typename container_T>
auto queue_mutex_t<type_T, container_T>::is_empty() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_container.empty();
}
}
