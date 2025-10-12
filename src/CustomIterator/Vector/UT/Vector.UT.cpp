#include "Vector.h"

#include <algorithm>
#include <fmt/core.h>
#include <gtest/gtest.h>

using namespace ape;

static auto* const fakeBeginPointer{reinterpret_cast<int*>(0)};
auto FakeAllocator(std::size_t) {
    return fakeBeginPointer;
}

TEST(Vector, GetBegin)
{
    // Arrange
    auto expectedBeginPointer{fakeBeginPointer};
    auto vectorSize{1};
    Vector vector(vectorSize, FakeAllocator);

    // Act
    auto beginIterator {vector.begin()};
    auto actualBeginPointer{beginIterator.GetRawPointer()};

    // Asse
    EXPECT_EQ(expectedBeginPointer, actualBeginPointer);
}

TEST(Vector, GetEnd)
{
    // Arrange
    const auto vectorSize{2};
    const auto expectedEndPointer{fakeBeginPointer + vectorSize};
    Vector vector(vectorSize, FakeAllocator);

    // Act
    auto endIterator{vector.end()};
    auto actualEndIterator{endIterator.GetRawPointer()};

    // Assert
    EXPECT_EQ(expectedEndPointer, actualEndIterator);
}

TEST(Vector, GetBack) {
    const auto vectorSize{2};
    const auto expectedBackPointer{fakeBeginPointer + vectorSize - 1};
    Vector vector(vectorSize, FakeAllocator);

    // Act
    auto backIterator{vector.back()};
    auto actualBackIterator{backIterator.GetRawPointer()};

    // Assert
    EXPECT_EQ(expectedBackPointer, actualBackIterator);
}

TEST(Vector, AlgorithmFill) {
    // Arrange
    const auto vectorSize{4U};
    Vector vector(vectorSize);

    // Act
    std::generate(vector.begin(), vector.end(), [n = 1]() mutable {
        return n++;
    });

    // Assert
    auto iterator = vector.begin();
    EXPECT_EQ(1, *iterator);
    EXPECT_EQ(2, *(++iterator));
    EXPECT_EQ(3, *(++iterator));
    EXPECT_EQ(4, *(++iterator));
}
