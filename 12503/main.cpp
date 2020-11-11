#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    int cases, size, c = 1;
    int position, index;
    string command;
    bitset<1 << 7> instructions;

    // Calculating scarecrows
    cin >> cases;

    while (cases--)
    {
        cin >> size;
        position = 0;
        instructions.reset();

        for (int i = 0; i < size; ++i)
        {
            cin >> command;
            if (command == "RIGHT")
            {
                instructions[i] = 1;
                ++position;
            }
            else if (command == "LEFT")
            {
                --position;
            }
            else
            {
                cin >> command >> index;
                if (instructions[index - 1])
                {
                    instructions[i] = 1;
                    ++position;
                }
                else
                {
                    --position;
                }
            }
        }
        cout << position << endl;
    }
    return 0;
}
