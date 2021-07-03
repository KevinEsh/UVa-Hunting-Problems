#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct corner{
    int weight;
    int sum;
    corner() : weight(0), sum(0) {}
};

int main(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int dim, num_cor, maxi;
    vector<corner> corners;

    while (cin >> dim) {
        corners.clear();
        num_cor = 1 << dim;
        maxi = 0;
        
        //Lectura de los pesos
        for(int i=0; i < num_cor; i++) {
            corner pick;
            cin >> pick.weight;
            corners.push_back(pick);
        }

        //Calculo de la potencia de la esquina
        for (int i=0; i < num_cor; i++) {
            for (int j=0; j < dim; j++) {
                corners[i].sum += corners[(i ^ (1 << j))].weight;
            }
        }

        //Busqueda de las dos esquinas vecinas con mayor suma 
        for (int i=0; i < num_cor; i++) {
            for (int j=0; j < dim; j++) {
                maxi = max(maxi, corners[i].sum + corners[(i ^ (1 << j))].sum);
            }
        }

        cout << maxi << endl;
    }

    return 0;
}
