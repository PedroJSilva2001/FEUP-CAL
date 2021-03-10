#include "exercises.h"
using namespace std;
int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int best = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a; b < n; b++) {
            int sum = 0;
            for (int k = a; k <= b; k++) {
                sum+=A[k];
            }
            //best = max(sum, best);
            if (sum > best) {
                best = sum;
                i = a;
                j = b;
            }
        }
    }
    return best;
}

int maxSubsequenceN2(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int best = 0, sum;

    for (int a = 0; a < n; a++) {
        sum = 0;
        for (int b = a; b < n; b++) {
            sum += A[b];
            //best = max(best,sum);
            if (sum > best) {
                best = sum;
                i = a; //se nao fosse preciso atualizar i e j este if vai com o boda
                j = b;
            }
        }
    }
    return best;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceN2(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}