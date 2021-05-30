#include "exercises.h"

#include <sstream>

// Time: O(n^2), Space: O(n)
std::string calcSum(int sequence[], unsigned long n) {
    // Assumes n <= 10000
    long sum[10000]; // sum[i] = sum of the subsequence of length i+1 with the smallest sum
    unsigned long index[10000]; // index[i] = start index of the subsequence of length i+1 with the smallest sum

    // Step 1: Experiment with different start indices
    for(unsigned long i = 0; i < n; i++) {
        long val = 0; // sum of subsequence starting at index i
        for(unsigned long j = i; j < n; j++) {
            val += sequence[j];
            if(i == 0 || val < sum[j-i]) {
                sum[j-i] = val;
                index[j-i] = i;
            }
        }
    }

    // Step 2: Build the solution
    std::ostringstream oss;
    for(unsigned long i = 0; i < n; i++) {
        oss << sum[i] << "," << index[i] << ";";
    }
    return oss.str();
}

#include <iostream>
#include <chrono>

void testPerformanceCalcSum() {
    srand(time(NULL)); //generates random seed
    int seq[10000];
    const unsigned int N_ITERATIONS = 20;
    const unsigned long MIN_SIZE = 0;
    const unsigned long MAX_SIZE = 10000;
    const unsigned long STEP_SIZE = 500;

    std::cout << "n; time (ms)" << std::endl;
    for (unsigned long size = MIN_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int k = 0; k < N_ITERATIONS; k++) {
            for (unsigned long i = 0; i < size; i++) {
                seq[i]= rand() % (10 * size) + 1;
            }
            std::string res = calcSum(seq, size);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << size << ";" << (elapsed / N_ITERATIONS) << std::endl;
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));

    // Uncomment the next line to perform the execution time tests
    // testPerformanceCalcSum();
}