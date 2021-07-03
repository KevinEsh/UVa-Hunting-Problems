#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define Q 8

int get_grid(vector<int> &permutation, vector<int> &solution) {
    int distance = 0;

    for (int i=0; i < Q; i++) {
        if (permutation[i] != solution[i])
            distance++;
    }

    return distance;
}

int main(void) {
    int pos, cases = 0;
    vector<int> permutation;
    vector< vector<int> > solutions;

    for(int i=0; i< Q; i++) {
        permutation.push_back(i);
    }

    do {
        set<int> queen1, queen2;

        for (int i=0; i < Q; i++) {
            queen1.insert(permutation[i] + i);
            queen2.insert(permutation[i] - i);
        }

        if (Q == queen1.size() && Q == queen2.size()) {
            solutions.push_back(permutation);
        }
    } while (next_permutation(permutation.begin(), permutation.end()));


    while (cin >> pos) {
        
        cases++;
        permutation.clear();
        permutation.push_back(pos-1);

        for (int i=0; i < Q-1; i++) {
            cin >> pos;
            permutation.push_back(pos-1);
        }

        int result = 999999999;

        for(int i=0; i < solutions.size(); i++)
            result = min(result, get_grid(permutation, solutions[i]));

        cout << "Case " << cases << ": " << result << endl;
    }

    return 0;
}
