#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


typedef pair<int, int> interval;

bool by_smaller(const interval &a, const interval &b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

void solve(int M, vector<interval> &segments, vector<interval> &coverage) {
    int end = 0;
    int index = 0;
    bool first = true;
    interval seg = make_pair(-1, -1);
    
    for (int index = 0; index < segments.size(); index++) {

        if (segments[index].first <= end) {
            if (first) {
                seg = segments[index];
                first = false;
            } else if (segments[index].second > seg.second) {
                seg = segments[index];
            }
            
        } else {

            //si es el primero y es mayor que 0, entonces no existe posibilidad de cubrir el rango [0,M]
            if (first)
                break;

            coverage.push_back(seg);
            end = seg.second;
            first = true;
            if (end >= M) break;
        }
    }

    if (!first) coverage.push_back(seg);
}

int main(void) {
    int cases, M;
    pair<int,int> seg;

    cin >> cases;

    for (int c =0; c < cases; c++) {
        cin >> M;
        vector<interval> segments;
        vector<interval> coverage;

        while (cin >> seg.first >> seg.second) {
            if (seg.second < 0) continue;
            if (seg.first == 0 && seg.second == 0) break;
            if (seg.first == seg.first) continue;
            segments.push_back(seg);
        }

        sort (segments.begin(), segments.end(), by_smaller);

        if (segments[0].first > 0) {
            cout << 0 << endl;
        } 
        
        else {

            solve(M, segments, coverage);

            if (coverage.empty() || coverage[coverage.size()-1].second < M)
                cout << 0 << endl;
            else {
                cout << coverage.size() << endl;
                for (int i=0; i < coverage.size(); i++ )
                    cout << coverage[i].first << " " << coverage[i].second << endl;
            }
        }

        if (cases) cout << endl;
    }

    return 0;
}
