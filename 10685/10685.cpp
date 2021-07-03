#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ufds.h"
using namespace std;

int main(void) {
  int c, r;
  string input, anotherinput;

  while (cin >> c >> r) {
    if (c == 0 && r == 0)
      break;

    int counter = 0;
    map<string,int> m;
    UFDSet DSet(c);

    cin.ignore(100, '\n');
    while (c--) {
      getline(cin ,input);
      m[input] = counter;
      counter++;
    }

    int result = 1;
    while (r--) {
      cin >> input >> anotherinput;
      DSet.union_sets(m[input], m[anotherinput]);
      if (DSet.get_size(m[input]) > result)
        result = DSet.get_size(m[input]);
    }

    cout << result << endl;
  }

  return 0;
}