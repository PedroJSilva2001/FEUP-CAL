#include "exercises.h"
#include "algorithm"
#include "vector"
using namespace std;
bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}
bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}
std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {
    vector<Activity> res;
    sort(A.begin(),A.end());
    unsigned int lastFinishTime = 0;
    for(auto &u : A){
        if(u.start >= lastFinishTime){
            res.push_back(u);
            lastFinishTime = u.finish;
        }
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(V,  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}