// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>

// Time: O(n*MaxStock*T), Space: O(n*MaxStock*T)
bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    const unsigned int INF_N_COINS = T + 1;
    unsigned int minCoins[10][11][1001]; // assumes n <= 19, Stock[i] <= 10 for all i, and T <= 1000
    unsigned int lastCoin[10][11][1001];

    // Step 1: Initialize the auxiliary tables
    for(unsigned int i = 0; i < n; i++) {
        for(unsigned int s = 0; s <= Stock[i]; s++) {
            minCoins[i][s][0] = 0;
            for(unsigned int k = 1; k <= T; k++) {
                minCoins[i][s][k] = INF_N_COINS;
            }
        }
    }
    // For i = 0
    for(unsigned int s = 1; s <= Stock[0]; s++) {
        for(unsigned int k = C[0]; k <= T; k++) {
            if(k % C[0] == 0 && k / C[0] <= s) {
                minCoins[0][s][k] = k / C[0];
                lastCoin[0][s][k] = 0;
            }
        }
    }

    // Step 2: Compute minCoins
    for(unsigned int i = 1; i < n; i++) {
        // Case s = 0
        for(unsigned int k = 1; k <= T; k++) {
            minCoins[i][0][k] = minCoins[i-1][Stock[i-1]][k];
            lastCoin[i][0][k] = lastCoin[i-1][Stock[i-1]][k];
        }
        // Case s > 0
        for(unsigned int s = 1; s <= Stock[i]; s++) {
            for(unsigned int k = 1; k <= T; k++) {
                if(k >= C[i]) {
                    if(minCoins[i][s-1][k - C[i]] < minCoins[i-1][Stock[i-1]][k]) {
                        minCoins[i][s][k] = 1 + minCoins[i][s-1][k - C[i]];
                        lastCoin[i][s][k] = i;
                    }
                    else {
                        minCoins[i][s][k] = minCoins[i-1][Stock[i-1]][k];
                        lastCoin[i][s][k] = lastCoin[i-1][Stock[i-1]][k];
                    }
                }
                else {
                    minCoins[i][s][k] = minCoins[i-1][Stock[i-1]][k];
                    lastCoin[i][s][k] = lastCoin[i-1][Stock[i-1]][k];
                }
            }
        }
    }

    /*
     * For debugging purposes, it prints the DP matrix
    for(unsigned int i = 0; i < n; i++) {
        std::cout << "\n\nFor i = " << i << ":\n\n";
        for(unsigned int s = 0; s <= Stock[i]; s++) {
            std::cout << "For s = " << s << ": ";
            for(unsigned int k = 0; k <= T; k++) {
                std::cout << lastCoin[i][s][k] << " "; // change to minCoins[i][s][k] if needed
            }
            std::cout << "\n";
        }
    }
    */

    // Step 3: Check if a solution was found
    if(minCoins[n-1][Stock[n-1]][T] == INF_N_COINS) return false;

    // Step 4: Build the solution
    for(unsigned int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }

    int remainingT = T;
    int curI = n-1;
    int curStock = Stock[curI];
    while(remainingT > 0) {
        int nextI = lastCoin[curI][curStock][remainingT];
        std::cout << "minCoins = " << minCoins[curI][curStock][remainingT] << "\n";
        std::cout << "nextI = " << nextI << "\n";
        usedCoins[nextI]++;
        remainingT -= C[nextI];
        curI = nextI;
        curStock = Stock[curI] - usedCoins[curI];
    }
    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];
    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}