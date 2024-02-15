#include <iostream>
using namespace std;

const int MAXT = 1e7;
const int MAXM = 1e4;
long long f[MAXT];

int main() {
    int T, m;
    cin >> T >> m;
    for (int i = 1, t, v; i <= m; i++) {
        cin >> t >> v;
        for (int j = t; j <= T; j++) {
            f[j] = max(f[j], f[j - t] + v);
        }
    }
    cout << f[T] << endl;
    return 0;
}