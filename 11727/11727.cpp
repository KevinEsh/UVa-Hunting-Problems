#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main()
{
    int cases;
    int salaries[3];
    
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> salaries[0] >> salaries[1] >> salaries[2];
        sort(salaries, salaries+3);
        cout << "Case " << c << ": " << salaries[1] << "\n";
    }  
}