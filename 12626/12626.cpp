#include<iostream>
#include<string>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cases, m, a, r, g, i, t, pizzas;
    string cadena;

    cin >> cases;
    for (int c=0; c < cases; c++){
        m = a = r = g = i = t = pizzas = 0;

        cin >> cadena; //lectura de la cadena

        for(int j = 0; j < cadena.size(); j++){
            if(cadena[j] == 'M') m++;
            else if(cadena[j] == 'A') a++;
            else if(cadena[j] == 'R') r++;
            else if(cadena[j] == 'G') g++;
            else if(cadena[j] == 'I') i++;
            else if(cadena[j] == 'T') t++;

            // La cadena "margarita" esta completa?
            if(m >= 1 && a >= 3 && r >= 2 && g >= 1 && i >= 1 && t >= 1){
                m = m - 1;
                a = a - 3;
                r = r - 2;
                g = g - 1;
                i = i - 1;
                t = t - 1;
                pizzas++;
            }
        }

        cout << pizzas << "\n";
    }

    return 0;
}
