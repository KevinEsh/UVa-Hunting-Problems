#include <iostream>
#include <cstring>
using namespace std;

#define MINUT 1000005
bool calendar[MINUT];

int main(void) {
    int n, m, a, b, rep, s, e;
    bool conflict;

    while (cin >> n >> m) {
        if (n == 0 && m == 0) 
            break;

        conflict = true;
        memset(calendar, false, MINUT);

        while (n--) {
            cin >> a >> b;

            for (int i = a; i < b; i++) {
                if (calendar[i])
                    conflict = false;

                calendar[i] = true;
            }
        }

        while(m--) {
            cin >> a >> b >> rep;

            for (int i = 0; b + i * rep < MINUT; i++) {
                s = a + i * rep;
                e = b + i * rep;

                for (int j = s; j < e; j++) {
                    if (calendar[j])
                        conflict = false;

                    calendar[j] = true;
                }
            }
        }

        if (conflict) cout << "NO CONFLICT" << endl;
        else cout << "CONFLICT" << endl;
    }

    return 0;
}
