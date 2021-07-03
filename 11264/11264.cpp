#include <iostream>
#include <vector>
using namespace std;

int main(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> coins;
    int cases, num_coins, coin;
    int total, suma;

    cin >> cases;
    for (int c=0; c < cases; c++) {
        cin >> num_coins;

        for(int i=0; i < num_coins; i++) {
            cin >> coin;
            coins.push_back(coin);
        }

        total = suma = 1;
        for (int i = 1; i < num_coins; i++) {
            if (i == num_coins-1) total++;
            else {
                if (suma + coins[i] < coins[i+1]) {
                    total++;
                    suma += coins[i];
                }
            }
        }

        cout << total << endl;
    }

    return 0;
}
