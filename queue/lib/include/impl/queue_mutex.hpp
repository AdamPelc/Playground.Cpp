#include <mutex>
#include <deque>
#include <optional>
#include <stdexcept>
#include <stdexcept>

namespace impl
{

template<typename type_T, typename container_T = std::deque<type_T>>
class queue_mutex_t
{
public:
    [[nodiscard]]
    auto dequeue() const -> std::optional<type_T>;
    auto enqueue(type_T value) -> void;

private:
    container_T m_container;
};

template<typename type_T, typename container_T>
std::optional<type_T> queue_mutex_t<type_T, container_T>::dequeue() const
{
    if (m_container.empty()) {
        return {};
    }
    return m_container.front();
}

template<typename type_T, typename container_T>
auto queue_mutex_t<type_T, container_T>::enqueue(type_T value) -> void {
    m_container.push_back(value);
}
}
