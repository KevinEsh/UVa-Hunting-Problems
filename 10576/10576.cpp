#include <iostream>
#include <vector>
using namespace std;

int s, d;
long long maxi;
vector<int> bugs;

void yk2() {

    if (bugs.size() > 4) {
        int sum = 0;
        for (int i=0; i < 5; i++) 
            sum += bugs[bugs.size() - 1 - i];

        if (sum >= 0) return;
    }

    if (bugs.size() == 12) {
        int sum = 0;
        for (int i=0; i < 12; i++) 
            sum += bugs[i];
        
        if (sum > maxi) maxi = sum;
    
        return;
    }

    bugs.push_back(s);
    yk2();
    bugs.pop_back();
    bugs.push_back(d);
    yk2();
    bugs.pop_back();
}

int main(void) {
    while (cin >> s >> d) {
        d = -d;
        maxi = -1;
        yk2();

        if (maxi == -1) cout << "Deficit" << endl;
        else cout << maxi << endl;
    }

    return 0;
}
