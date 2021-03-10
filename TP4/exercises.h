// By: Gonçalo Leão

#ifndef CAL_TP4_CLASSES_EXERCISES_H
#define CAL_TP4_CLASSES_EXERCISES_H

#include <string>

// Ex 1
// Recursive version
unsigned long factorialRecurs(unsigned long n);
// Version with dynamic programming
unsigned long factorialDP(unsigned long n);

// Ex 2
bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 3
bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 4
std::string calcSum(int sequence[], unsigned long n);
void testPerformanceCalcSum();

// Ex 5
unsigned long s_recursive(unsigned int n, unsigned int k);
unsigned long b_recursive(unsigned int n);
unsigned long s_dynamic(unsigned int n, unsigned int k);
unsigned long b_dynamic(unsigned int n);

// Ex 6
int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j);
void testPerformanceMaxSubsequence();

#endif //CAL_TP4_CLASSES_EXERCISES_H
