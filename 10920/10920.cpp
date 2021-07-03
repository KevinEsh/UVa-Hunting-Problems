#include <iostream>
using namespace std;

typedef long long ll;

pair<int,int> coordinate(int size, ll pos) {
    int x, y, direction = 0; //la direccion inicial es hacia arriba
    int increment = 1, count = 2;
    ll current = 1;

    x = y = size / 2 + 1; //celda 1
    if (pos == 1) return make_pair(x, y);

    while (current != pos) {
        if (current + increment >= pos) {
            increment = pos - current;
        }

        count--;
        current += increment;

        switch (direction % 4) {
            case 0: //hacia arriba
                x += increment;
                break;
            case 1: //hacia la izquierda
                y -= increment;
                break;
            case 2: //hacia abajo
                x -= increment;
                break;
            case 3: //hacia la derecha
                y += increment;
                break;
        }
        direction++;

        if (count == 0) {
            increment++;
            count = 2;
        }
    }

    return make_pair(x, y);
}

int main(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int size;
    ll pos;

    while (cin >> size >> pos) {
        if (size == 0 && pos == 0) break;
        auto coor = coordinate(size, pos);
        cout << "Line = " << coor.first << ", column = " << coor.second << "." << endl;
    }

    return 0;
}
