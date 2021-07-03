#include <iostream>
#include <limits>
#include "geocom.cpp"
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor position, closer, station;
    Segment rail;
    int num;
    double mini, dist;
    double a1, a2, b1, b2;

    while( cin >> position.x){
        cin >> position.y;
        cin >> num;
        mini = numeric_limits<double>::max(); 

        
        cin >> a1 >> a2;
        for (int r = 0; r < num; r++){
            cin >> b1 >> b2;

            rail.set_tensor1(a1, a2);
            rail.set_tensor2(b1, b2);
            rail.size();

            station = rail.closer_to(position);
            dist = (station - position).norma();
            a1 = b1; a2 = b2;

            if (dist < mini) {
                mini = dist;
                closer = station;
            }
        }

        printf("%.4f\n%.4f\n", closer.x, closer.y);

    }
    
}