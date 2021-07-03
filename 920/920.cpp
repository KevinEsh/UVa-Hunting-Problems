#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define EPS 10e-9
typedef pair<double, double> Coor;

bool greaters(const Coor &a,  const Coor &b) { 
    if (fabs(a.first - b.first) > EPS){
        return (a.first > b.first);
    }
    else{
        return (a.second > b.second);
    }
} 

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Coor> mountain;
    int cases, num;
    double x, y;
    double sunrise, height;
    double nume, deno, alpha;

    cin >> cases;
    for (int c = 0; c < cases; c++){
        mountain.clear();
        
        cin >> num;
        for (int i = 0; i < num; i++){
            cin >> x >> y;
            mountain.push_back( make_pair(x, y) );
        }
        
        sort(mountain.begin(), mountain.end(), greaters);

        sunrise = 0.0;
        height = 0.0;

        auto former = mountain.begin();
        for (auto current = ++mountain.begin(); current != mountain.end(); ++current){
            if (current->second > height){
                nume = height - former->second;
                deno = current->second - former->second;
                
                if (fabs(deno) < EPS) {
                    sunrise += current->second - height;
                }
                else {
                    alpha = nume/deno;
                    sunrise += sqrt( pow((1-alpha)*(current->first - former->first), 2) + pow( current->second - height, 2) );  
                }
                height = current->second;
            }
            former = current;
        }

        printf("%.2f\n", sunrise );
    }

    return 0;
}