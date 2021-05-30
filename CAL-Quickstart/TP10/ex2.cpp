#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;
int min3(int a, int b, int c) {
    return min(min(a,b), c);
}

int editDistance(std::string pattern, std::string text) {
    int **dp = new int * [pattern.size()+1];
    for (unsigned i = 0; i <= pattern.size(); i++) {
        dp[i] = new int [text.size()+1];
    }
    // dynamic programming uwu :)))
    for (int i = 0; i <= pattern.size(); ++i) {
        for (int j = 0; j <= text.size(); ++j) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (pattern[i-1] == text[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min3(dp[i][j-1],
                                     dp[i-1][j],
                                     dp[i-1][j-1]);
        }
    }
    int mintEditDistance = dp[pattern.size()][text.size()];

    // quem se esquece de dar delete a memoria alocada é paneleiro
    for (int i = 0; i < pattern.size(); i++) {
        if (dp[i] != nullptr) {
            delete[] dp[i];
        }
    }
    delete[] dp;

    return mintEditDistance;
}

float numApproximateStringMatching(std::string filename, std::string toSearch) {
    float avg = 0;
    unsigned n = 0;
    string word;
    ifstream t(filename);
    while (t >> word) {
        avg += (float)editDistance(toSearch, word);
        n++;
    }
    return avg/n;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex2, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex2, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}