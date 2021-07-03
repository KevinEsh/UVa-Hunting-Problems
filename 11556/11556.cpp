#include <iostream>
#include <cmath>
using namespace std;

int main(void) {
    unsigned long long n, count;
    int b;

    while (cin >> n >> b) {
        count = pow(2, b+1) - 1;

        if (n <= count) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
