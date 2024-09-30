#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "n 값: ";
    cin >> n;

    vector<int> isPrime;

    for (int i = 0; i <= n; i++) {
        isPrime.push_back(i);
    }

    for (auto it = isPrime.begin() + 2; it != isPrime.end(); ++it) {
        int prime = *it;
        if (prime != 0) {  
            for (int j = prime * prime; j <= n; j += prime) {
                isPrime[j] = 0;  
            }
        }
    }


    cout << "소수 목록:" << endl;
    for (auto it = isPrime.begin() + 2; it != isPrime.end(); ++it) {
        if (*it != 0) {
            cout << *it << " ";
        }
    }
    cout << endl;

    return 0;
}
