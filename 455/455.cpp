#include <iostream>
#include <string>
using namespace std;

int main(void) {
  int cases;
  bool found;
  string cadena;

  cin >> cases;
  for (int c = 0; c < cases; c++) {

    cin >> cadena;

    for (int i = 1, size = cadena.size(); i <= size; i++) {
      if (size % i != 0)
        continue;

      string sub_cadena = string(cadena.begin(), cadena.begin() + i);
      string pattern = "";

      for (int j = 0; j < size / i; j++)
        pattern += sub_cadena;

      if (pattern == cadena) {
        cout << sub_cadena.size() << "\n\n";
        break;
      }
    }
  }

  return 0;
}
