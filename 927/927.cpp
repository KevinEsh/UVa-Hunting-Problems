#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef unsigned long long ull;

int main() {
    vector<int> coeff;
    int cases, degree, value, d, k;
    int index, n, size;

    cin >> cases;    
    for (int c = 0; c < cases; c++) {

        cin >> degree;
        
        //Lectura de los coefficientes
        coeff.clear();
        for (int i = 0; i < degree+1; i++) {
            cin >> value;
            coeff.push_back(value);
        }

        cin >> d >> k;

        // Busqueda de la potencia n en la que esta el indice k
        index = 0;
        n = 1;
        while (index + n * d < k) {
            index += n * d;
            n++;
        }

        //Calculo del valor con el teorema de Horner
        size = coeff.size();
        ull suma = coeff[size-1];
        for (int i = size-2; i >= 0; i--) {
            suma = coeff[i] + n * suma;
        }

        cout << suma << endl;
    }

    return 0;
}
