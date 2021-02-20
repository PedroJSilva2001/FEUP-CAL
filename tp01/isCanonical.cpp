#include <algorithm>
using namespace std;
unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

bool isCanonical(unsigned int C[], unsigned int n) {
    int smallNum = C[2] + 1;
    int bigNum = C[n-1] + C[n-2];

    unsigned int st1[n];
    unsigned int st2[n];
    unsigned int res1[n];
    unsigned int res2[n];

    for(int i = 0; i < n; i++){
        st1[i] = 10;
        st2[i] = 10;
    }


    for(int i = smallNum; i <= bigNum; i++){
        changeMakingBF(C,st1,n,i,res1);
        changeMakingGreedy(C,st2,n,i,res2);
        if(sumArray(res1,n) != sumArray(res2,n)) return false;
    }
    return true;
}