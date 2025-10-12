#include "fibonacci.h"
#include <gtest/gtest.h>

TEST(Fibonacci, IndexZero)
{
    // Arrange
    const auto expected = 0;

    // Act
    const auto actual = fibonacci(0);

    // Assert
    EXPECT_EQ(expected, actual);
}
