#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "ufds.h"
using namespace std;

int main(void) {
  int cases;
  int n;
  string a, b;

  cin >> cases;

  for (int c=0; c < cases; c++) {
    int counter = 0;
    map<string,int> dictionary;
    UFDSet DSet(200000);

    cin >> n;

    while (n--) {
      cin >> a >> b;

      if (dictionary.find(a) == dictionary.end()) {
        dictionary[a] = counter;
        counter++;
      }

      if (dictionary.find(b) == dictionary.end()) {
        dictionary[b] = counter;
        counter++;
      }

      DSet.union_sets(dictionary[a], dictionary[b]);
      cout << DSet.get_size(dictionary[a]) << endl;
    }
  }

  return 0;
}
