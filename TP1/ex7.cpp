#include "exercises.h"
#include <algorithm>
using namespace std;
#include <vector>
/*
 * a) Considerando a duração da atividade i como di, sendo ci o tempo de conclusão da atvidade i
 * então ci = ci-1 + di, (c0 = d0). Queremos minimizar sum(ci)/n logo queremos minimizar sum((n-i)*di)/n.
 *
 * b) sum((n-i)*di)/n = (n*sum(di) - sum(i*di))/n a unica parte da equação que não é constante é sum(i*di)
 * e pretendemos maximizá-la, tal é conseguido quando di está ordenado por ordem crescente.
 */
double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {
    unsigned int taskSum = 0;
    unsigned int numTasks = tasks.size();
    orderedTasks = tasks;
    sort(orderedTasks.begin(), orderedTasks.end());

    for(int i = 0; i < numTasks; i++){
        taskSum += (numTasks-i)*orderedTasks[i];
    }

    return (double)taskSum/numTasks;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {
    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}