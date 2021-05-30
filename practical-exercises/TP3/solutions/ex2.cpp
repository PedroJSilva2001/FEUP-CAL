// By: Gonçalo Leão

#include "exercises.h"

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
// Justification for time: Master theorem (https://brilliant.org/wiki/master-theorem/)
// General recursive temporal complexity is T(n) = a*T(n/b) + f(n).
// In this case, we have a = 2, b = 2, so c_crit = log(a) / log(b) = log(2) / log(2) = 1,
// The work needed to merge is f(n) = Θ(n) = Θ(n^c_crit) = Θ(n) (case 2 is satisfied)
// Thus, since this corresponds to case 2, T(n) = Θ((n^c_crit) * log(n) = Θ(nªlog(n)).
// Note: Θ(n) means that the complexity is O(n) and Ω(n), in other words:
// There is some integers k1, k2 and n0 such that, when n > n0:
// k1*n <= T(n) <= k2*n
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if(n == 0) return 0;
    else return maxSubsequenceDCRec(A,0,n-1,i,j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}