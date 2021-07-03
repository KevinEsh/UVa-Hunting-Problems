#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define MAX 10000

int main(void) {
  int n;
  int books[MAX];
  int money;
  pair<int,int> best;

  while (cin >> n) {
    for (int i = 0; i < n; i++)
      cin >> books[i];

    cin >> money;
    
    best.first = 0;
    best.second = 2000000000; //maximo dinero

    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {

        if (books[i] + books[j] == money) {
          if (abs(books[i] - books[j]) < abs(best.first - best.second)) {
            best.first = min(books[i], books[j]);
            best.second = max(books[i], books[j]);
          }
        }
      }
    }

    cout << "Peter should buy books whose prices are " << best.first << " and " << best.second << "." << endl << endl;
  }

  return 0;
}
