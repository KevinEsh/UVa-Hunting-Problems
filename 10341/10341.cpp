#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
#define EPS 1e-8

int p, q, r, s, t, u;

double f(double x) {
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

double binary_search() {
	double inf = 0, sup = 1;
	while (inf + EPS < sup) {
		double x = (inf + sup) / 2;
		if (f(inf) * f(x) <= 0) sup = x;
		else inf = x;
	}
	return sup;
}

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	while (cin >> p >> q >> r >> s >> t >> u) {
		if (f(0) * f(1) > 0)
			cout << "No solution" << endl;
		else
			printf("%.4f\n", binary_search());
	}

	return 0;
}
