#include <iostream>
#include <bitset>

using namespace std;

int main()
{
    int cases, size, c = 1;
    int scarecrows;
    char cell;
    bitset<1 << 7> field;

    // Calculating scarecrows
    cin >> cases;

    while (cases--)
    {
        cin >> size;
        scarecrows = 0;
        field.reset();

        for (int i = 0; i < size; ++i)
        {
            cin >> cell;
            if (cell == '.')
            {
                field[i] = 1;
            }
        }

        for (int i = 0; i < size; ++i)
        {
            // Greedily make a scarecrow cover 3 cells.
            if (field[i])
            {
                field[i] = field[i + 1] = field[i + 2] = 0;
                ++scarecrows;
            }
        }
        cout << "Case " << c++ << ": " << scarecrows << endl;
    }
    return 0;
}
