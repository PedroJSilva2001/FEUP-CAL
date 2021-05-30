// By: Gonçalo Leão

#include "exercises.h"

// Time: O(n), Space: O(n)
// Kadane's algorithm
int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    if(n == 0) return 0;

    int bestSum = A[0];
    int curSum = A[0];
    i = 0;
    unsigned int curI = 0;
    j = 0;
    for(unsigned int k = 1; k < n; k++) {
        if(curSum >= 0) {
            // Extend the current subsequence
            curSum += A[k];
        }
        else {
            // Start a new subsequence
            curI = k;
            curSum = A[k];
        }

        if(curSum > bestSum) {
            bestSum = curSum;
            i = curI;
            j = k;
        }
    }
    return bestSum;
}

// Time: O(n^3), Space: O(n)
int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    if(n == 0) return 0;

    bool firstSum = true;
    int maxSum;
    for(unsigned int a = 0; a < n; a++) {
        for(unsigned int b = a + 1; b < n; b++) {
            int sum = 0;
            for(unsigned int c = a; c <= b; c++) {
                sum += A[c];
            }
            if(firstSum) {
                firstSum = false;
                maxSum = sum;
                i = a;
                j = b;
            }
            else if(sum > maxSum) {
                maxSum = sum;
                i = a;
                j = b;
            }
        }
    }
    return maxSum;
}

int maxSubsequenceDCRec(int A[], int start, int finish, int &i, int &j) {
    // Base case
    if(start == finish) {
        i = start;
        j = finish;
        return A[start];
    }

    // Step 1: Split
    int start2 = (int)round((start + finish) / 2.0);
    int finish1 = start2 - 1;
    int i1, j1;
    int i2, j2;
    int bestSum1 = maxSubsequenceDCRec(A,start,finish1,i1,j1);
    int bestSum2 = maxSubsequenceDCRec(A,start2,finish,i2,j2);

    // Step 2: Merge
    // Find the best solution that crosses the midpoint
    int curSum = A[finish1];
    int bestCrossingSum1 = A[finish1];
    int bestCrossingI = finish1;
    for(int k = finish1 - 1; k >= start; k--) {
        curSum += A[k];
        if(curSum > bestCrossingSum1) {
            bestCrossingSum1 = curSum;
            bestCrossingI = k;
        }
    }

    curSum = A[start2];
    int bestCrossingSum2 = A[start2];
    int bestCrossingJ = start2;
    for(int k = start2 + 1; k <= finish; k++) {
        curSum += A[k];
        if(curSum > bestCrossingSum2) {
            bestCrossingSum2 = curSum;
            bestCrossingJ = k;
        }
    }
    int bestCrossingSum = bestCrossingSum1 + bestCrossingSum2;

    // Choose the best solution of the three
    if(bestCrossingSum > bestSum1 && bestCrossingSum > bestSum2) {
        i = bestCrossingI;
        j = bestCrossingJ;
        return bestCrossingSum;
    }
    else if(bestSum1 > bestSum2){
        i = i1;
        j = j1;
        return bestSum1;
    }
    else {
        i = i2;
        j = j2;
        return bestSum2;
    }
}

// Time: O(n*log(n)), Space: O(n), where n is the number of elements in A
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if(n == 0) return 0;
    else return maxSubsequenceDCRec(A,0,n-1,i,j);
}

#include <iostream>
#include <chrono>

void testPerformanceMaxSubsequence() {
    srand(time(NULL)); //generates random seed
    const unsigned long N_ITERATIONS = 5;
    const unsigned long MIN_SIZE = 0;
    const unsigned long MAX_SIZE = 10000;
    const unsigned long STEP_SIZE = 500;
    int seq[MAX_SIZE];

    std::cout << "n; DP time (s); BF time (s); DC time (s)" << std::endl;
    for(unsigned long size = MIN_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        auto elapsedDP = std::chrono::duration<double>::zero();
        auto elapsedBF = std::chrono::duration<double>::zero();
        auto elapsedDC = std::chrono::duration<double>::zero();
        for(unsigned long k = 0; k < N_ITERATIONS; k++) {
            for(unsigned long i = 0; i < size; i++) {
                seq[i] = rand() % (10 * size) - (5 * size);
            }

            unsigned int i, j;
            auto start = std::chrono::high_resolution_clock::now();
            for(unsigned int k = 0; k < N_ITERATIONS; k++) {
                maxSubsequenceDP(seq, size, i, j);
            }
            auto finish = std::chrono::high_resolution_clock::now();
            elapsedDP += finish - start;

            start = std::chrono::high_resolution_clock::now();
            for(unsigned int k = 0; k < N_ITERATIONS; k++) {
                maxSubsequenceBF(seq, size, i, j);
            }
            finish = std::chrono::high_resolution_clock::now();
            elapsedBF += finish - start;

            int i2, j2;
            start = std::chrono::high_resolution_clock::now();
            for(unsigned int k = 0; k < N_ITERATIONS; k++) {
                maxSubsequenceDC(seq, size, i2, j2);
            }
            finish = std::chrono::high_resolution_clock::now();
            elapsedDC += finish - start;
        }
        std::cout << size << ";" << (elapsedDP.count() / N_ITERATIONS) << ";" << (elapsedBF.count() / N_ITERATIONS) << ";" << (elapsedDC.count() / N_ITERATIONS) << std::endl;
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    // Uncomment the next line to perform the execution time tests
    // testPerformanceMaxSubsequence();
}