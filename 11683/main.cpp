#include <iostream>

using namespace std;

int main()
{
    int height, lenght;
    int sculped_height;
    int laser_beams;

    // Getting laser beams
    while (cin >> height >> lenght)
    {
        if (!height && !lenght)
        {
            break;
        }

        laser_beams = 0;

        for (int i = 0; i < lenght; ++i)
        {
            cin >> sculped_height;
            if (sculped_height < height)
            {
                laser_beams += (height - sculped_height);
                height = sculped_height;
            }
            else if (sculped_height > height)
            {
                height = sculped_height;
            }
        }
        cout << laser_beams << endl;
    }
    return 0;
}
