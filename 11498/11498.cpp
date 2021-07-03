#include <iostream>

using namespace std;

int main()
{
    int cases;
    int center_x, center_y;
    int ubi_x, ubi_y;

    while (cin >> cases)
    {
        cin >> center_x >> center_y;
        for (int c=0; c < cases; c++)
        {
            cin >> ubi_x >> ubi_y;
            if (center_x == ubi_x || center_y == ubi_y ) cout << "divisa" << "\n";
            else if (center_x < ubi_x && center_y < ubi_y) cout << "NE" << "\n";
            else if (center_x > ubi_x && center_y < ubi_y) cout << "NO" << "\n";
            else if (center_x > ubi_x && center_y > ubi_y) cout << "SO" << "\n";
            else if (center_x < ubi_x && center_y > ubi_y) cout << "SE" << "\n";
        }
    }    

    return 0;
} 

