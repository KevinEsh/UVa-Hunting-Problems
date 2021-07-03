#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int size_password, value;
    int maxi, argmaxi, last;
    string cadena;

    while (cin >> size_password) {

        cin >> cadena;

        map<string,int> dictionary;
        last = cadena.size() -size_password + 1;
        maxi = 0;

        for (int i = 0; i < last; i++) {
            value = dictionary[cadena.substr(i,size_password)]++;
            if (value > maxi) {maxi = value; argmaxi = i;}
        }

    cout << cadena.substr(argmaxi,size_password) << endl;

    }
    return 0;
}