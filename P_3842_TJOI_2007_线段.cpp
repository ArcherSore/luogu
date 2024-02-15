#include <iostream>
using namespace std;

const int MAXN = 2e4 + 5;
int f[MAXN][2];
int r[MAXN], l[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        if (i == 1) {
            f[i][0] = 2 * r[i] - l[i] - 1, f[i][1] = r[i] - 1;
        } else {
            f[i][0] = min(r[i] - l[i] + abs(r[i - 1] - r[i]) + f[i - 1][1], r[i] - l[i] + abs(l[i - 1] - r[i]) + f[i - 1][0]);
            f[i][1] = min(r[i] - l[i] + abs(l[i - 1] - l[i]) + f[i - 1][0], r[i] - l[i] + abs(r[i - 1] - l[i]) + f[i - 1][1]);
        }
        // cout << f[i][0] << ", " << f[i][1] << endl;
    }
    cout << min(f[n][0] + n - l[n], f[n][1] + n - r[n]) + n - 1 << endl;
    return 0;
}