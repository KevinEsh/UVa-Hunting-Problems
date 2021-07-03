#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int main(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector< stack<char> > contenedores;
    string cadena;
    int cases = 0;

    while (cin >> cadena) {
        if (cadena == "end") break;
        cases++;
        contenedores.clear();


        for (int i=0; i < cadena.size(); i++) {
            bool found = false;

            for (int j=0; j < contenedores.size(); j++) {
                if (contenedores[j].top() >= cadena[i]) {
                    found = true;
                    contenedores[j].push(cadena[i]);
                    break;
                }
            }

            if (!found) {
                stack<char> ship;
                ship.push(cadena[i]);
                contenedores.push_back(ship);
            }
        }

        cout << "Case " << cases << ": " << contenedores.size() << endl;
    }

    return 0;
}
