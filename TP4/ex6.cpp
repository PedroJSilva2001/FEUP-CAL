#include "exercises.h"

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int best = 0, sum = 0;
    int J, I;
    for (int k = 0; k < n; k++) {
        //sum = max(A[k],sum+A[k]);
        if (A[k] >= sum+A[k]) {
            sum = A[k];
            I = k;  //se nao fosse preciso atualizar i e j nao é preciso os ifs
            J = I;
        }
        else {
            sum += A[k];
            J = k;
        }
        //best = max(best,sum);
        if (sum > best) {
            i = I;
            j = J;  //se nao fosse preciso atualizar i e j nao é preciso os ifs
            best = sum;
        }
    }
    return best;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
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
#include <limits>
using namespace std;

int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j, int l, int r) {
    if(l == r) {
        i = l, j = r;
        return A[l];
    }
    unsigned int li,lj,ri,rj;
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
int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    //return maxSubsequenceDC(A,n,i,j,0,n-1);
    return maxSubsequenceDC(A, n, i, j, 0, n-1);
}

void testPerformanceMaxSubsequence() {
	// TODO
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

    testPerformanceMaxSubsequence();
}