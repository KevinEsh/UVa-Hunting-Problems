#include <iostream>
#include <vector>
#include "geocom.cpp"
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor point;
    double area_tile, container;
    int num_points, index = 0;

    while (cin >> num_points) {
        index++;
        Polygon tile;
        if ( num_points == 0) break;
        
        for (int i = 0; i < num_points; i++) {
            cin >> point.x >> point.y;
            tile.add(point);
        }
        
        //Obtenemos el area de los puntos
        tile.close();
        area_tile = tile.get_area();
        
        //Convertimos la figura en su envolvente convexa y obtenemos el area
        tile.convex_hull();
        container = tile.get_area();

        printf("Tile #%d\nWasted Space = %.2f %%\n\n", index, 100.0*(container - area_tile)/container);
    }
}