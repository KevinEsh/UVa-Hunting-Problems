#include <iostream>
#include <vector>
#include "geocom.cpp"
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor point1, point2;
    Tensor centroid, pivot;
    vector<Line> lines;
    double strip;
    int num_points, index = 0;

    while (cin >> strip >> num_points) {
        if ( num_points == 0 && strip == 0) break;

        //Construimos las lineas del poligono a la vez que calculamos el centroide
        cin >> point1.x >> point1.y;
        centroid = point1;
        pivot = point1;
        lines.clear();

        for (int i=0; i < num_points-1; i++) {
            cin >> point2.x >> point2.y;
            centroid.x += point2.x;
            centroid.y += point2.y;
            Line line(point1, point2);
            lines.push_back(line);
            point1 = point2;
        }
        Line line(point1, pivot);
        lines.push_back(line);
        centroid.x /= num_points;
        centroid.y /= num_points;
        
        //Movemos las lineas una distancia de forma paralela.
        int num = (int)lines.size();
        for (int i=0; i < num; i++){
            lines[i].shift_to(centroid, strip);
        }

        //Encuentra la interseccion de las nuevas lineas
        Polygon polygon;
        for (int i=0; i < num -1; i++){
            polygon.add( lines[i] % lines[i+1]);
        }
        polygon.add( lines[0] % lines[num-1]);

        //Imprime el area del poligono recortado
        printf("%.3f\n", polygon.get_area());
    }
}