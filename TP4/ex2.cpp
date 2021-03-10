#include "exercises.h"
#include <vector>
#include <unordered_map>
using namespace std;
bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    /*int Max = T + 1;
    vector<int> dp(T + 1, Max);
    dp[0] = 0;
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < n; j++) {    //menos eficiente porque vê permutações e não combinações
            if (C[j] <= i) {
                dp[i] = min(dp[i], dp[i - C[j]] + 1);
            }
        }
    }


    if (dp[T] <= T) return true;
    return false;*/

    vector<int> dp1(T+1, T+1);  //min coins
    dp1[0] = 0;
    int dp2[T+1];   //last coins
    dp2[0] = 0;

    /*for (int i = 0; i <= n; i++) {
        for (int j = C[i]; j <= T; j++) {
            //dp1[j] = min(dp1[j], dp1[j-C[i]] +1);
            if (dp1[j - C[i]] + 1 < dp1[j]){
                dp1[j] = 1 + dp1[j - C[i]];
                dp2[j] = C[i];
            }
        }
    }*/
    /*if (dp1[T] <= T) return true;
    return false;*/

    for (int i = 1; i <= n; i++)
        for (int k = C[i - 1]; k <= T; k++)
            if (dp1[k - C[i - 1]] + 1 < dp1[k])
            {
                dp1[k] = 1 + dp1[k - C[i - 1]];
                dp2[k] = C[i - 1];
            }

    if(dp1[T] > T) return false;

    /*map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(make_pair(C[i], 0));
    }
    for (int i = T; i > 0; i -= dp2[i]) {
        int value = mp.at(dp2[i]);
        mp.erase(dp2[i]);
        mp.insert(make_pair(dp2[i], value+1));
    }
    for (auto p : mp) {

    }*/
    unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(make_pair(C[i], i));
    }
    for (int i = T; i > 0; i -= dp2[i]) {
        usedCoins[mp.at(dp2[i])]++;
    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    usedCoins[0] = 0;
    usedCoins[1] = 0;
    usedCoins[2] = 0;
    usedCoins[3] = 0;
    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
    usedCoins[0] = 0;
    usedCoins[1] = 0;
    usedCoins[2] = 0;
    usedCoins[3] = 0;
    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);
    usedCoins[0] = 0;
    usedCoins[1] = 0;
    usedCoins[2] = 0;
    usedCoins[3] = 0;
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