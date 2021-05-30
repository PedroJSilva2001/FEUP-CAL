#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int kmpMatcher(std::string text, std::string pattern) {
    int occurences = 0;
    auto P = pattern.size();
    unsigned *pi = new unsigned [P];
    unsigned k = 0;
    pi[0] = 0;

    for (unsigned i = 1; i < P; ++i) {
        while (k > 0 && pattern.at(k) != pattern.at(i-1)) {
            k = pi[k-1];
        }
        if (pattern.at(k) == pattern.at(i)) {
            k++;
        }
        pi[i] = k;
    }

    unsigned T = text.size();
    unsigned charMatches = 0;

    for (int i = 0; i < T; ++i) {
        while (charMatches > 0 && pattern.at(charMatches) != text.at(i)) {
            charMatches = pi[charMatches-1];
        }
        if (pattern.at(charMatches) == text.at(i)) {
            charMatches++;
        }
        if (P == charMatches) {
            occurences++;
            charMatches = pi[charMatches-1];
        }
    }
    delete[] pi;
    return occurences;
}

int numStringMatching(std::string filename, std::string toSearch) {
    ifstream t(filename);
    string text((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());
    return kmpMatcher(text, toSearch);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}