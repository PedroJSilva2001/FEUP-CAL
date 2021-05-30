#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int best = 0, sum;

    for (int a = 0; a < n; a++) {
        sum = 0;
        for (int b = a; b < n; b++) {
            sum += A[b];
            //best = max(sum, best);
            if (sum > best) {  // o if ia de boda se não fosse preciso atualizar o i e o j
                best = sum;
                i = a;
                j = b;
            }
        }
    }

    return best;
}

//the implementation above is smarter because it adds A[i] in the second loop
int maxSubsequence_n3(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int best = 0;

    for (int a = 0; a < n; a++) {
        for (int b = a; b < n; b++) {
            int sum = 0;
            for (int k = a; k <= b; k++) {
                sum += A[k];
            }

            if (sum > best) {
                best = sum;
                i = a;
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
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}