#include <iostream>
#include <bitset>
#include <string>
using namespace std;

#define MAX 100
int suma[MAX+2] = {0};

void sum_fibonary(string num1, string num2){
    bitset<MAX> fib1(num1);
    bitset<MAX> fib2(num2);
    int maxs = (num1.size() > num2.size())? num1.size(): num2.size();
    for (int i=maxs-1; i >= 0; i--){
        suma[i] = fib1[i] + fib2[i];
    }

    bool flag = true;
    while (flag){
        flag = false;
        for (int i=0; i <= maxs + 1; i++){
            if (suma[i] > 1){
                if (i == 0){
                    suma[i+1] += 1;
                    suma[i] = 0;
                }
                else {
                    suma[max(0, i-2)] += 1;
                    suma[i+1] += 1;
                    suma[i] = 0;
                }
                flag = true;
            }
            else if (suma[i]==1 && suma[i+1]==1){
                suma[i+2] += 1;
                suma[i+1] = 0;
                suma[i] = 0;
                flag = true;
            }

        }
    }

    if (suma[maxs+1])
        for (int i = maxs+1; i>= 0; i--) cout << suma[i];
    else if (suma[maxs])
        for (int i = maxs; i>= 0; i--) cout << suma[i];
    else 
        for (int i = maxs-1; i>= 0; i--) cout << suma[i];
}

int main(){    
    string fib1, fib2;

    while (cin >> fib1 >> fib2)
    {
        sum_fibonary(fib1, fib2);
        cout << "\n\n";
    }
}