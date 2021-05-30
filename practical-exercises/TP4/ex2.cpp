#include "exercises.h"
#include <unordered_map>
#include <vector>
using namespace std;

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for (unsigned i = 0; i < n; ++i) {
        usedCoins[i] = 0;
    }
    /*int Max = T + 1;
    vector<int> dp(T + 1, Max);
    dp[0] = 0;
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < n; j++) {    //less effiecient because computes permutations instread of combinations
            if (C[j] <= i) {
                dp[i] = min(dp[i], dp[i - C[j]] + 1);
            }
        }
    }
    if (dp[T] <= T) return true;
    return false;*/

    vector<int> dp1(T+1, T+1);  //min coins
    dp1[0] = 0;
    //int dp2[T+1];   //last coins
    //dp2[0] = 0;
    vector<int> dp2(T+1, -1); //last coins

    for (int i = 0; i <= n; i++) {
        for (int k = C[i]; k <= T; k++) {
            //dp1[k] = min(dp1[k], dp1[k-C[i]] +1);
            if (dp1[k - C[i]] + 1 < dp1[k]) {
                dp1[k] = 1 + dp1[k - C[i]];
                //dp2[k] = C[i];
                dp2[k] = i;
            }
        }
    }

    if(dp1[T] > T) {
        return false;
    }

    /*unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(make_pair(C[i], i));
    }
    for (int i = T; i > 0; i -= dp2[i]) {
        usedCoins[mp.at(dp2[i])]++;
    }*/
    while(T > 0){
        usedCoins[dp2[T]]++;
        T -= C[dp2[T]];
    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}