#include <algorithm>
using namespace std;
bool changeMakingGreedy(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for(int i = n-1; i >= 0; i--){
        usedCoins[i] = min(T/C[i], Stock[i]);
        T -= usedCoins[i]*C[i];
    }
    return T == 0;
}