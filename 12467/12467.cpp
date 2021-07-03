#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 1000007

int match[MAX];

void preprocess(const string &p) {
    match[0] = -1;
    for (int i=0,j=-1; i < p.size(); i++, j++) {
        while (j>=0 && p[i]!=p[j]) j=match[j];
        i++;j++;
        match[i]=j;
    }
}

int knuth_morris_pratt(const string &cadena, const string &pattern) {
    int len=-1;
    for (int i=0, j=0; i < cadena.size(); i++, j++) {

        if (j>=0 && cadena[i] != pattern[j]) 
            while (j>=0 && cadena[i]!=pattern[j]) 
                j = match[j];
        else
            if (j > len) len= j;
    }
    return len;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int cases;
    string cadena;
    cin >> cases;
    for (int c=0; c < cases; c++) {

        cin >> cadena;
        string secret(cadena); 
        reverse(secret.begin(),secret.end());

        preprocess(cadena);

        int len= knuth_morris_pratt(secret, cadena);
        if (len >= cadena.size()) len = cadena.size()-1;
        for (int j=len; j >=0 ; j--)
            cout << cadena[j];
            cout << endl;
        }
    return 0;
}
