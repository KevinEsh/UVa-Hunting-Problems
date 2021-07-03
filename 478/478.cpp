#include <iostream>
#include <vector>
#include <map>
#include "geocom.cpp"
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tensor point;
    Tensor grid(9999.9, 9999.9);
    Tensor t1, t2, t3;

    vector<Circle> circles;
    vector<Triangule> triangles;
    vector<Rectangule> rectangles;
    map<int,pair<int,char> > dictionary;

    char figure;
    double radio;
    int id, index = 1;

    while (true){

        cin >> figure;
        if (figure == '*') break;

        switch (figure) 
        {
            case 'c':{
                cin >> t1.x >> t1.y;
                cin >> radio;

                circles.push_back( Circle(radio, t1));
                dictionary[index++] = make_pair(circles.size()-1,'c');
                break;}

            case 'r':{
                cin >> t1.x >> t1.y;
                cin >> t2.x >> t2.y;

                rectangles.push_back( Rectangule(t1, t2));
                dictionary[index++] = make_pair(rectangles.size()-1,'r');
                break;}

            case 't':{
                cin >> t1.x >> t1.y;
                cin >> t2.x >> t2.y;
                cin >> t3.x >> t3.y;

                triangles.push_back( Triangule(t1, t2, t3));
                dictionary[index++] = make_pair(triangles.size()-1,'t');
                break;}
        }
    } 

    int num_fig = 0;
    while (cin >> point.x >> point.y) {

        if (point == grid) break;
        bool inside = false, empty = true;
        num_fig++;

        for (int k = 1; k < index; k++) {
            id = dictionary[k].first;
            figure = dictionary[k].second;

            switch (figure)
            {
            case 'c':
                inside = circles[id].is_inside(point);
                break;

            case 'r':
                inside = rectangles[id].is_inside(point);
                break;

            case 't':
                inside = triangles[id].is_inside(point);
                break;
            }

            if (inside) {
                cout << "Point " << num_fig << " is contained in figure " << k << endl;
                empty = false;
            }
        }

        if (empty) cout << "Point " << num_fig << " is not contained in any figure\n";
    }

    return 0;
}