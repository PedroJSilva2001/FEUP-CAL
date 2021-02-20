#include <iostream>
#include <unordered_set>
using namespace std;

bool sum3_N3(unsigned int T, unsigned int selected[3]) {
    for (unsigned i = 1; i < T; i++) {
        for (unsigned j = 1; i < T; i++) {
            for (unsigned k = 1; i < T; i++) {
                if (T == i+j+k) {
                    selected[0] = i;
                    selected[1] = j;
                    selected[2] = k;
                    return true;
                }
            }
        }
    }
    return false;
}

bool sum3_N2(unsigned int T, unsigned int selected[3]) {
    unordered_set<unsigned> hs;
    for (unsigned i = 1; i < T; i++) {
        hs.insert(i);
    }
 //o hash set aqui nao é preciso porque estámos a ver todos os números de 1 a T
 //se fosse fornecido um array em que não sabemos o range seria preciso o hash set  
    for (unsigned i = 1; i < T; i++) {
        for (unsigned j = 1; i < T; i++) {
            if (hs.find(T-i-j) != hs.end()) {
                selected[0] = i;
                selected[1] = j;
                selected[2] = T-i-j;
                return true;
            }
        }
    }
    return false;
}


int main() {

    unsigned s[3];

    if (sum3_N3(8547, s))
        cout << s[0] << " " << s[1] << " " << s[2];
    
    return 0;
}
