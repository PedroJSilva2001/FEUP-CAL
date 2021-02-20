#include <vector>

#define INF 1e6
using namespace std;

int changeMakingRecursive(unsigned int C[], vector<unsigned int> Stock, int n, int T, vector<unsigned int> &usedCoins){
    if(T < 0) return INF;
    if(T == 0) return 0;
    int result = INF;
    vector<unsigned int> ans;
    vector<unsigned int> copy = usedCoins;
    for(int i = 0; i < n; i++){
        if(Stock[i] == 0) continue;
        Stock[i] --;
        int x = changeMakingRecursive(C,Stock,n,T-C[i],usedCoins);
        usedCoins[i]++;
        if(1+x < result) {
            ans = usedCoins;
            result = 1 + x;
        }
        Stock[i]++;
        usedCoins = copy;
    }
    usedCoins = ans;
    return result;
}




bool isCorrect(unsigned int C[], unsigned int usedCoins[], unsigned int n, unsigned int T){
    unsigned int totalValue = 0;
    for(int i = 0; i < n; i++){
        totalValue += C[i]*usedCoins[i];
    }
    return totalValue == T;
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int numCoins = INF;
    unsigned int mod[n];
    unsigned int coins[n];
    unsigned int stockProduct = 1;
    unsigned int stockSum = 0;
    for(int i = 0;  i< n; i++){
        coins[i] = Stock[i];
        stockSum += Stock[i];
        mod[i] = stockProduct;
        stockProduct*=(Stock[i]+1);
    }
    for(int j = 1; j <= stockProduct; j++){
        if(isCorrect(C,coins,n,T) && stockSum < numCoins){
            numCoins = stockSum;
            for(int i = 0; i < n; i++){
                usedCoins[i] = coins[i];
            }
        }
        for(int i = 0; i < n; i++){
            if(j%mod[i] == 0){
                if(coins[i] != 0){
                    coins[i]--;
                    stockSum--;
                }else{
                    coins[i] = Stock[i];
                    stockSum += Stock[i];
                }
            }
        }
    }
    return numCoins != INF;
}