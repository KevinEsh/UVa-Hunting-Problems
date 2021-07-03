#include <iostream>
#include <set>
using namespace std;

typedef unsigned long long ull;

int main(void) {
  int n, k, money;
  ull suma;
  multiset<int> moneys;

  while (cin >> n) {
    if (n == 0)
      break;

    moneys.clear();
    suma = 0;

    for (int i = 0; i < n; i++) {
      cin >> k;
      for (int c =0; c < k; c++) {
        cin >> money;
        moneys.insert(money);
      }

      auto it1 = moneys.begin();
      auto it2 = moneys.rbegin();
      money = *it2;

      suma += *it2 - *it1;

      moneys.erase(it1);
      it1 = moneys.find(money);
      moneys.erase(it1);
    }

    cout << suma << endl;
  }

  return 0;
}
