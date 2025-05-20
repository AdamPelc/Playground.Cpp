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
    auto front() const -> std::optional<type_T>;

    [[nodiscard]]
    auto pop() -> std::optional<type_T>;

    auto push(type_T value) -> void;

    [[nodiscard]]
    auto empty() const -> bool;

private:
    container_T m_container;
};

template<typename type_T, typename container_T>
std::optional<type_T> queue_mutex_t<type_T, container_T>::front() const
{
    if(empty())
    {
        return {};
    }

    throw std::runtime_error("Not implemented");
}

template<typename type_T, typename container_T>
std::optional<type_T> queue_mutex_t<type_T, container_T>::pop()
{
    if(empty())
    {
        return {};
    }

    throw std::runtime_error("Not implemented");
}

template<typename type_T, typename container_T>
void queue_mutex_t<type_T, container_T>::push(type_T value)
{
    throw std::runtime_error("Not implemented");
}

}