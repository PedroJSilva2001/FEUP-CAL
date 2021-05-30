// By: Gonçalo Leão

#include "exercises.h"

// Time: O(n), Space: O(n)
unsigned long factorialRecurs(unsigned long n) {
    return (n == 0) ? 1 : n*factorialRecurs(n-1);
}

// Time: O(n), Space: O(1)
unsigned long factorialDP(unsigned long n) {
    unsigned long fact = 1;
    for(unsigned long i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, FactorialTest) {
    EXPECT_EQ(1,factorialRecurs(0));
    EXPECT_EQ(1,factorialRecurs(1));
    EXPECT_EQ(2,factorialRecurs(2));
    EXPECT_EQ(6,factorialRecurs(3));
    EXPECT_EQ(24,factorialRecurs(4));
    EXPECT_EQ(120,factorialRecurs(5));
    EXPECT_EQ(3628800,factorialRecurs(10));

    EXPECT_EQ(1,factorialDP(0));
    EXPECT_EQ(1,factorialDP(1));
    EXPECT_EQ(2,factorialDP(2));
    EXPECT_EQ(6,factorialDP(3));
    EXPECT_EQ(24,factorialDP(4));
    EXPECT_EQ(120,factorialDP(5));
    EXPECT_EQ(3628800,factorialDP(10));
}