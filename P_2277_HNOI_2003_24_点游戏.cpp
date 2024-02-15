#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-7;

double a[4];

double cal(double i, double j, int opt) {
    if (opt == 0) return i + j;
    if (opt == 1) return i - j;
    if (opt == 2) return i * j;
    if (opt == 3) {
        if (j == 0) return 10000.0;
        return i / j;
    }
    return 10000.0;
}

int main() {
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    sort(a, a + 4);

    int res = 0;
    do {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int p = 0; p < 4; p++) {
                    res += abs(cal(cal(a[0], a[1], i), cal(a[2], a[3], p), j) - 24.0) < EPS;
                    res += abs(((cal(a[0], a[1], i), a[2], j), a[3], p) - 24.0) < EPS;
                }
            }
        }
    } while (next_permutation(a, a + 4));
    cout << res << endl;
    return 0;
}