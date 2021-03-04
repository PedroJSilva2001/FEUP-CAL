#include "exercises.h"
#include <limits>
using namespace std;

const int MIN_INT = std::numeric_limits<int>::min();
const int INT_MAX = std::numeric_limits<int>::max();

int max3(int a, int b, int c) {return max(max(a, b),c);}

int maxCrossingSum(int A[], int l, int m, int r, int &i, int &j) {
    int sum = 0;
    int lBestSum = MIN_INT, rBestSum = MIN_INT;

    for (int k = m; k >= l; k--) {
        sum += A[k];
        if (lBestSum < sum) {
            lBestSum = sum;
            i = l;
            //j = k;
        }
    }
    sum = 0;
    for (int k = m + 1; k <= r; k++) {
        sum += A[k];
        if (rBestSum < sum) {
            rBestSum = sum;
            //i = k;
            j = r;
        }
    }
    return max3(lBestSum + rBestSum, lBestSum, rBestSum);

}

int maxSubSequenceRecursion(int A[], int l, int r, int &i, int &j) {
    if (l == r) {
        //i = l;
        //j = l;
        return A[l];
    }

    int m = (l+r)/2;

    return max3(maxSubSequenceRecursion(A, l, m, i, j),
                maxSubSequenceRecursion(A, m+1, r, i , j),
                maxCrossingSum(A, l, m, r, i, j));
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j, int l, int r) {
    if(l == r) {
        i = l, j = r;
        return A[l];
    }
    int li,lj,ri,rj;
    int m = (l+r)/2;
    int lmax = maxSubsequenceDC(A,n,li,lj,l,m);
    int rmax = maxSubsequenceDC(A,n,ri,rj,m+1,r);
    int dmax;

    if(lmax > rmax){
        dmax = lmax;
        i = li;
        j = lj;
    } else{
        dmax = rmax;
        i = ri;
        j = rj;
    }

    int mmax= 0, mi, mj;
    int best = -INT_MAX, tot = 0;
    for(int ii = m; ii >= l; ii--){
        tot += A[ii];
        if(tot > best){
            best = tot;
            mi = ii;
        }
    }
    mmax += best;

    best = -INT_MAX, tot = 0; //Reset values
    for(int ii = m+1; ii <= r; ii++){
        tot += A[ii];
        if(tot > best){
            best = tot;
            mj = ii;
        }
    }
    mmax += best;

    if(mmax > dmax){
        dmax = mmax;
        i = mi;
        j = mj;
    }
    return dmax;
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {

    //int res = maxSubSequenceRecursion(A, 0, n-1, i, j);
    //return res;
    return maxSubsequenceDC(A,n,i,j,0,n-1);
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