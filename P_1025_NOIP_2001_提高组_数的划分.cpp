#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int f[MAXN][10];

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][1] = 1;
        for (int j = 2; j <= min(i, k); j++) {
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }
    cout << f[n][k] << endl;
    return 0;
}