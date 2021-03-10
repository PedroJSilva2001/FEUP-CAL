#include "exercises.h"
#include <unordered_set>
using namespace std;
bool sum3(unsigned int T, unsigned int nums[3]) {
    //a verdade é que isto não T^3 porque acaba sempre no
    //tuplo (T-2, 1, 1) visto que se pede para retornar logo
    //o primeiro que se encontra
    for (unsigned i = 1; i < T; i++) {
        for (unsigned j = 1; i < T; i++) {
            for (unsigned k = 1; i < T; i++) {
                if (T == i+j+k) {
                    nums[0] = i;
                    nums[1] = j;
                    nums[2] = k;
                    return true;
                }
            }
        }
    }
    return false;
}

bool sum3_n2(unsigned int T, unsigned int nums[3]) {
    unordered_set<unsigned> hs;
    for (unsigned i = 1; i < T; i++) {
        hs.insert(i);
    }
    //o hash set aqui nao é preciso porque estámos a ver todos os números de 1 a T
    //se fosse fornecido um array em que não sabemos o range seria preciso o hash set
    for (unsigned i = 1; i < T; i++) {
        for (unsigned j = 1; i < T; i++) {
            if (hs.find(T-i-j) != hs.end()) {
                nums[0] = i;
                nums[1] = j;
                nums[2] = T-i-j;
                return true;
            }
        }
    }
    return false;
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