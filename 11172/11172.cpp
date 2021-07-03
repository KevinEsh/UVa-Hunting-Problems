#include <iostream>

using namespace std;

int main()
{
    int cases;
    int num1, num2;
    cin >> cases;

    for (int c = 0; c < cases; c++)
    {

        cin >> num1 >> num2;

        if (num1 > num2)
            cout << ">"
                 << "\n";
        else if (num1 < num2)
            cout << "<"
                 << "\n";
        else
            cout << "="
                 << "\n";
    }

    return 0;
}