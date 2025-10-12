#pragma once

#include <functional>
#include <utility>

template <typename T, typename TParameter>
class named_type_t {
public:
    using value_type_t = T;

    named_type_t() = default;
    explicit named_type_t(T const& value) : m_value(value) {}
    explicit named_type_t(T&& value) : m_value(std::move(value)) {}

    operator T() const { return m_value; }

    T& get() { return m_value; }
    [[nodiscard]] const T& get() const { return m_value; }

private:
    T m_value{};
};

template <typename T>
struct named_type_hasher_t {
    std::size_t operator()(T const& obj) const noexcept {
        return std::hash<typename T::value_type_t>()(obj.get());
    }
};
