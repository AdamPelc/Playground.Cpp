#include "Vector.h"

#include <gtest/gtest.h>

#include <limits>

using namespace ape;

TEST(VectorIterator, GetValueReference) {
    // Arrange
    int expectedIteratorValue{std::numeric_limits<int>::max()};
    Vector::Iterator iterator(&expectedIteratorValue);

    // Act && Assert
    EXPECT_EQ(expectedIteratorValue, *iterator);
}

TEST(VectorIterator, GetRawPointerWithNullptr) {
    // Arrange
    auto expectedPointer = nullptr;
    Vector::Iterator iterator(expectedPointer);

    // Act
    const auto actualPointer = iterator.GetRawPointer();

    // Assert
    EXPECT_EQ(expectedPointer, actualPointer);
}

TEST(VectorIterator, GetRawPointerWithNotNullptr) {
    // Arrange
    auto expectedPointer = reinterpret_cast<int*>(1);
    Vector::Iterator iterator(expectedPointer);

    // Act
    const auto actualPointer = iterator.GetRawPointer();

    // Assert
    EXPECT_EQ(expectedPointer, actualPointer);
}

TEST(VectorIterator, GetNextIterator) {
    // Arrange
    int values[] = {1, 2};
    Vector::Iterator iterator(values);
    Vector::Iterator expectedIterator(&values[1]);

    // Act && Assert
    ++iterator;

    EXPECT_EQ(expectedIterator, iterator);
}

TEST(VectorIterator, OperatorEqualityIsEqual) {
    // Arrange
    int iteratorValue{0};
    Vector::Iterator iterator1(&iteratorValue);
    Vector::Iterator iterator2(&iteratorValue);

    // Act && Assert
    EXPECT_TRUE(iterator1 == iterator2);
}

TEST(VectorIterator, OperatorEqualityIsNotEqual) {
    // Arrange
    int iterator1Value{0};
    Vector::Iterator iterator1(&iterator1Value);
    int iterator2Value{0};
    Vector::Iterator iterator2(&iterator2Value);

    // Act && Assert
    EXPECT_FALSE(iterator1 == iterator2);
}

TEST(VectorIterator, OperatorNotequalIsEqual) {
    // Arrange
    int iteratorValue{0};
    Vector::Iterator iterator1(&iteratorValue);
    Vector::Iterator iterator2(&iteratorValue);

    // Act && Assert
    EXPECT_FALSE(iterator1 != iterator2);
}

TEST(VectorIterator, OperatorNotequalIsNotEqual) {
    // Arrange
    int iterator1Value{0};
    Vector::Iterator iterator1(&iterator1Value);
    int iterator2Value{0};
    Vector::Iterator iterator2(&iterator2Value);

    // Act && Assert
    EXPECT_TRUE(iterator1 != iterator2);
}
