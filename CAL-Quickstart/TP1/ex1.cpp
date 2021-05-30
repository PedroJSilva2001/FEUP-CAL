#include "exercises.h"
#include <unordered_set>
using namespace std;

bool sum3(unsigned int T, unsigned int nums[3]) {
    vector<vector<unsigned>> perms;

    for (unsigned i = 1; i <= T; ++i) {
        for (unsigned j = 1; j <= T; ++j) {
            for (unsigned k = 1; k <= T; ++k) {
                if (i+j+k == T) {
                    perms.push_back({i, j, k});
                }
            }
        }
    }

    if (perms.empty()) {
        return false;
    }

    nums[0] = perms[0][0];
    nums[1] = perms[0][1];
    nums[2] = perms[0][2];
    return true;
}

bool sum3_n2(unsigned int T, unsigned int nums[3]) {
    unordered_set<unsigned> us;
    vector<vector<unsigned>> perms;

    for (unsigned i = 1; i <= T; i++) {
        us.insert(i);
    }
    // the unordered set is not really needed because we take into account all numbers
    // from 1 to T but we were supplied an array with an unknown range we would need it

    for (unsigned i = 1; i <= T; i++) {
        for (unsigned j = 1; i <= T; i++) {
            // If there exists the remaining number in the set which added up to i and j gives us T
            if (us.find(T-i-j) != us.end()) {
                perms.push_back({i, j, T-i-j});
            }
        }
    }
    if (perms.empty()) {
        return false;
    }

    nums[0] = perms[0][0];
    nums[1] = perms[0][1];
    nums[2] = perms[0][2];
    return true;
}
/// TESTS ///
#include <gtest/gtest.h>

void compareSums(unsigned int selected[3], unsigned int expectedSum) {
    EXPECT_EQ(selected[0] + selected[1] + selected[2], expectedSum);
}

TEST(TP1_Ex1, 3sumExists) {
    unsigned int selected[3];

    unsigned int T = 10;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);

    T = 18;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
}

TEST(TP1_Ex1, 3sumNotExists) {
    unsigned int selected[3];

    unsigned int T = 1;
    EXPECT_EQ(sum3(T,selected), false);
}