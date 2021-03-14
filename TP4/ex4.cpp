#include "exercises.h"

std::string calcSum(int sequence[], unsigned long n) {
    std::string ans;
    unsigned best, bestPos;

    for(unsigned i = 1; i <= n; i++) {
        best = 0;
        bestPos = 0;

        for(unsigned j = 0; j < i; j++)  {
            best += sequence[j];
        }

        unsigned accum = best;

        for(unsigned j = i; j < n; j++) {
            accum -= sequence[j-i];
            accum += sequence[j];

            if(accum < best) {
                bestPos = j-i+1;
                best = accum;
            }
        }

        ans += std::to_string(best) + "," + std::to_string(bestPos) + ";";
    }

    return ans;
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}