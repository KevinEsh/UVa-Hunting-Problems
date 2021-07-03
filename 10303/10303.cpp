#include <iostream>
#include <string>
#include "bignumber.cpp"
using namespace std;

/*  (2N + 2) * (2N + 1)
 *  ------------------- * CATALAN(N)
 *   (N + 1) * (N + 2)
 */

typedef unsigned long long ull;
#define MAX 100
ull catalan[31];
BigNum Catalan[71];

void ull_catalan(){

    catalan[1] = 1;
    
    for (int n = 2; n <= 30; n++)
        catalan[n] = catalan[n-1]*(2*n+2)*(2*n + 1) / ((n+1)*(n+2));
}

void BN_catalan(){

    Catalan[0] = BigNum(to_string(catalan[30]), true);

    for (int n = 31; n <= MAX; n++){
        int coeff = (2*n+2)*(2*n+1) / ((n+1)*(n+2));
        BigNum Coeff(to_string(coeff), true);
        Catalan[n-30] = Catalan[n-31] * Coeff;
    }
}


int main(){
    long long items;
    BigNum PI("2", true); //aproximadamene sqrt(pi)
    string number;

    ull_catalan();
    BN_catalan();

    while(cin >> items){

        if (items <= 30) cout << catalan[items] << endl;
        else cout << Catalan[items].get_number() << endl;
    }

    return 0;
}