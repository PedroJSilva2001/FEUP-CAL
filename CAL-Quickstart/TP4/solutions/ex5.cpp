#include "exercises.h"

// Time: O(n*k), Space: O(n*k)
unsigned long s_recursive(unsigned int n, unsigned int k) {
    if(k == 1 || n == k) return 1;
    else return s_recursive(n-1,k-1) + k*s_recursive(n-1,k);
}

// Time: O(n^2), Space: O(n^2)
unsigned long b_recursive(unsigned int n) {
    unsigned long sum = 0;
    for(unsigned int k = 1; k <= n; k++) {
        sum += s_recursive(n,k);
    }
    return sum;
}

// Time: O(n*k), Space: O(n), assuming n >= k
unsigned long s_dynamic(unsigned int n, unsigned int k) {
    unsigned int len = n - k + 1; // height of the column between (N,K) = (k,k) and (k,n)
    int strip[10000]; // a part of a column of the S(n,k) triangle, assumes n - k <= 9999

    // Initialize the strip for k=1 (all 1's)
    for(int i = 0; i < len; i++) {
        strip[i] = 1;
    }

    // Compute the values for the strip up to the given k
    // Values in the strip are computed along a diagonal (similar to C(n,k))
    for(int i = 2; i <= k; i++) {
        for(int j = 1; j < len; j++) {
            strip[j] += i * strip[j-1];
        }
    }

    return strip[len-1];
}

// Time: O(n^2), Space: O(n)
unsigned long b_dynamic(unsigned int n) {
    int line[1000]; // a line of the S(n,k) triangle, assumes n <= 1000

    // Compute the next lines up to the given n
    for(unsigned int i = 1; i <= n; i++) {
        line[i-1] = 1;
        for(unsigned int k = i - 1; k > 1; k--) {
            line[k-1] = line[k-2] + k*line[k-1];
        }
    }

    // Compute the sum of the last line
    unsigned long sum = 0;
    for(unsigned int k = 0; k < n; k++) {
        sum += line[k];
    }

    return sum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}