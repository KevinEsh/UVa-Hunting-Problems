#include <iostream>
#include <cmath>
#include "geocom.cpp"
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor vertex;
    int N;
    double radio, manhole;
    double thick, volume;

    while (cin >> N){
        if (N == 0) break;

        volume = 0.0;
        for (int i = 0; i < N; i++) {
            Polygon polygon;
            cin >> thick;
            cin >> vertex.x >> vertex.y;
            polygon.add(vertex); //Vertice inicial
            while(true){ //Se agregan vertices al poligono hasta que se de la vuelta al poligono
                cin >> vertex.x >> vertex.y;
                if (polygon.begin() == vertex)
                    break;
                polygon.add(vertex);
            }

            polygon.close();

            //Volumen del poligono
            volume += thick * polygon.get_area();
        }

        //Calculo del volumen del manhole
        cin >> radio >> thick;
        manhole = thick*M_PI*radio*radio;
        printf("%d\n", (int)(volume/manhole) );
    }

    return 0;
}