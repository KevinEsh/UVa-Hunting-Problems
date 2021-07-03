#include <iostream>
#include <string>
#include <cmath>

int main()
{
    int num;
    int sum;
    
    std::cout << "PERFECTION OUTPUT\n"; 
    while (std::cin >> num)
    {
        if (!num) break;

        sum = 1;
        for (int div = 2; div <= num / 2; div++) 
        {
            if (num % div == 0) sum += div;
        }

        if (num == 1) {std::cout << "    1  DEFICIENT\n"; continue;}

        int temp = num;
        int ten = 10000;
        std::string spaces = "";
        while (!(temp / ten))
        {
            spaces += " ";
            ten /= 10;
        }         

        std::cout << spaces << num; 
        if (sum == num) std::cout << "  PERFECT\n"; 
        else if (sum > num) std::cout << "  ABUNDANT\n"; 
        else std::cout << "  DEFICIENT\n"; 
    }
    std::cout << "END OF OUTPUT\n";
    
}