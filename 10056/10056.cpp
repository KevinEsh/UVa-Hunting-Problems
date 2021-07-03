#include <iostream>
#include <cmath>
using namespace std;

int main(){

    int cases, iplayer;
    double prob, num_players;
    double result;

    cin >> cases;
    for (int c=0;  c< cases; c++){
        cin >> num_players >> prob >> iplayer;
        result = prob*pow(1-prob, iplayer-1) / (1 -pow(1-prob, num_players)) ;
        printf("%.4f\n", result);
    }
    return 0;
}