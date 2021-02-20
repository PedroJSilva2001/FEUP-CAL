#include <vector>
#include <algorithm>
using namespace std;

class Activity {
public:
unsigned int start = 0;
unsigned int finish = 0;
Activity(unsigned int s, unsigned int f): start(s), finish(f){};
bool operator==(const Activity &a2) const;
bool operator<(const Activity &a2) const ;
};

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}



vector<Activity> earliestFinishScheduling(vector<Activity> A) {
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