#include <iostream>
#include <algorithm>
using namespace std;

int main(void) {
    int n;
    int boxes[10002];
    bool aviable[10002];
    int solution;
    bool first = true;

    while (cin >> n) {
        if (n == 0) break;

        if (first) first = false; else cout << endl;

        for (int i=0; i< n; i++) {
            cin >> boxes[i];
            aviable[i] = false;
        }

        sort(boxes, boxes + n);

        solution = 0;
        int prev = boxes[0];
        int counter = 1;

        for (int i= 1; i< n; i++) {
            if (boxes[i] == prev) {
                counter++;
            } else {
                if (counter > solution) solution = counter;
                counter = 1;
                prev = boxes[i];
            }
        }

        if (counter > solution) solution = counter;

        cout << solution << endl;
        for (int i=0; i< solution; i++) {
            for (int j = i; j < n; j += solution) {
                if (j > i) cout << " ";
                cout << boxes[j];
            }
            cout << endl;
        }
    }

    return 0;
}
