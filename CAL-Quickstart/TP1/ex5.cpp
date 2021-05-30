#include "exercises.h"

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;

    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }

    return sum;
}

bool isCanonical(unsigned int C[], unsigned int n) {
    int smallNum = C[2] + 1;
    int bigNum = C[n-1] + C[n-2];

    unsigned int st1[n];
    unsigned int st2[n];
    unsigned int res1[n];
    unsigned int res2[n];

    for(int i = 0; i < n; i++){
        st1[i] = 10;
        st2[i] = 10;
    }


    for(int i = smallNum; i <= bigNum; i++){
        changeMakingBF(C,st1,n,i,res1);
        changeMakingGreedy(C,st2,n,i,res2);
        if(sum(res1,n) != sum(res2,n)) return false;
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}