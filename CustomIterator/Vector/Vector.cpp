#include "Vector.h"

#include <fmt/core.h>

namespace ape {

int* Allocator(std::size_t size) {
    return new int[size];
}

auto Vector::Iterator::operator*() const -> reference {
    return *mPointer;
}

auto Vector::Iterator::operator++() -> Vector::Iterator& {
    ++mPointer;
    return *this;
}

Vector::Iterator Vector::begin() {
    return Vector::Iterator{mIntegers};
}

Vector::Iterator Vector::end() {
    return Vector::Iterator{mEnd};
}

Vector::Iterator Vector::back() {
    return Vector::Iterator{mEnd - 1};
}

Vector::Vector( std::size_t size, const std::function<int *( std::size_t )>& allocator ) : mIntegers{allocator(size)}, mEnd{mIntegers + size} {}

bool operator==( const Vector::Iterator& lhs, const Vector::Iterator& rhs ) {
    return lhs.GetRawPointer() == rhs.GetRawPointer();
}

bool operator!=( const Vector::Iterator& lhs, const Vector::Iterator& rhs ) {
    return lhs.GetRawPointer() != rhs.GetRawPointer();
}
}// namespace ape
