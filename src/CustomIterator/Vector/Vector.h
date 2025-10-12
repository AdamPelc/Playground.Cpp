#pragma once

#include <cstddef>
#include <functional>
#include <iterator>

namespace ape {

int* Allocator(std::size_t size);

class Vector {
public:
    struct Iterator {
        //        using iterator_category = std::forward_iterator_tag;
        //        using difference_type = std::ptrdiff_t;
        //        using value_type = int;
        using pointer   = int*;
        using reference = int&;

        explicit Iterator(pointer ptr) : mPointer{ptr} {}

        auto operator*() const -> reference;
        auto operator++() -> Iterator&;
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        [[nodiscard]] pointer GetRawPointer() const { return mPointer; }

    private:
        pointer mPointer{};
    };

    explicit Vector(std::size_t size,
                    const std::function<int*(std::size_t)>& allocator = Allocator);

    Iterator begin();
    Iterator end();
    Iterator back();

private:
    int* mIntegers{};
    int* mEnd{};
};

bool operator==(const Vector::Iterator& lhs, const Vector::Iterator& rhs);
bool operator!=(const Vector::Iterator& lhs, const Vector::Iterator& rhs);

}  // namespace ape
