
#include <iostream>
#include <algorithm>
using namespace std;


int maxSubsequenceN3(int A[], int n , unsigned int &i, unsigned int &j) {
    int best = 0, sum;
    for (int a = 0; a < n; i++) {
        for (int b = a; b < n; j++) {
            int sum = 0;
            i = a;
            j = b;
            for (int k = a; k <= b; k++) {
                sum+=k;
            }
            best = max(sum, best);
        }   
    }
    return best;  
}

int maxSubsequenceN2(int A[], int n , unsigned int &i, unsigned int &j) {
    int best = 0, sum;

    for (int a = 0; a < n; a++) {
        sum = 0;
        for (int b = a; b < n; b++) {
            sum += A[b];
            //best = max(best,sum);
            if (sum > best) {
                best = sum;
                i = a; //se nao fosse preciso atualizar i e j este if vai com o boda
                j = b;
            }
        }
    }
    return best;  
}

int maxSubsequenceN(int A[], int n , unsigned int &i, unsigned int &j) {
   int best = 0, sum = 0;
   int J, I;
    for (int k = 0; k < n; k++) {
        //sum = max(A[k],sum+A[k]);
        if (A[k] >= sum+A[k]) {
            sum = A[k];
            I = k;  //se nao fosse preciso atualizar i e j nao é preciso os ifs
            J = I;
        }
        else {
            sum += A[k];
            J = k;
        }
        //best = max(best,sum);
        if (sum > best) {
            i = I;
            j = J;  //se nao fosse preciso atualizar i e j nao é preciso os ifs
            best = sum;
        }
    }
    return best;  
}

int main() {

    int A[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned i, j;
    int a =  maxSubsequenceN(A, 9, i, j);
    cout << a << endl;
    cout << i << " " << j;
    return 0;
}