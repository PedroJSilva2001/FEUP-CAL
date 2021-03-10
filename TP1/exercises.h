#ifndef CAL_TP1_CLASSES_EXERCISES_H
#define CAL_TP1_CLASSES_EXERCISES_H

// Ex 1
bool sum3(unsigned int T, unsigned int nums[3]);

// Ex 2
int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j);

// Ex 3
bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 4
bool changeMakingGreedy(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 5
bool isCanonical(unsigned int C[], unsigned int n);

// Ex 6
#include <vector>

class Activity {
public:
    unsigned int start;
    unsigned int finish;
    Activity(unsigned int s, unsigned int f): start(s), finish(f){};
    bool operator==(const Activity &a2) const;
    bool operator<(const Activity &a2) const ;
    //TODO: Add other methods if needed
};
std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A);

// Ex 7
double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks);

#endif //CAL_TP1_CLASSES_EXERCISES_H
