#include <iostream>
#include <limits>
#include <cmath>
#include "geocom.cpp"
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor point1, point2, point3;
    Tensor mid1, mid2, center;
    double radius, angle;
    double xmin, xmax, ymin, ymax;
    double x, y;
    int num, count = 1;

    while ((cin >> num))
    {   
        if (num == 0) break;
        cin >> point1.x >> point1.y;
        cin >> point2.x >> point2.y;
        cin >> point3.x >> point3.y;

        //Puntos medios de los puntos dados
        mid1 = point1 + (point2 - point1)*0.5;
        mid2 = point2 + (point3 - point2)*0.5;

        //Pendientes de cada segmento
        Slope slope1(point1, point2);
        Slope slope2(point2, point3);
        
        //Ecuacion de rectas perpendiculares a los segmentos
        Line line1(mid1, slope1.perpendicular());
        Line line2(mid2, slope2.perpendicular());

        //Calculamos la intercecion de las dos lineas
        center = line1 % line2;
        radius = (point1 - center).norma();
        angle = atan2(point1.y - center.y, point1.x - center.x);

        //Bounding Box
        xmin = numeric_limits<double>::max();
        ymin = numeric_limits<double>::max();
        xmax = -numeric_limits<double>::max();
        ymax = -numeric_limits<double>::max();

        for (int i = 0; i < num; i++) {
            x = center.x + radius*cos(angle);
            y = center.y + radius*sin(angle);
            angle += M_PI*2.0/num;
            if (x < xmin) xmin = x;
            if (x > xmax) xmax = x;
            if (y < ymin) ymin = y;
            if (y > ymax) ymax = y;
        }

        printf("Polygon %d: %.3f\n", count, (xmax-xmin)*(ymax-ymin));
        count++;
    }
    
    return 0;
}