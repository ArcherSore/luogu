#include <bits/stdc++.h>
using namespace std;

int f[35][35] = {0};

int main() {
    int n, m;
    cin >> n >> m;

    f[0][1] = 1;
    for (int j = 1; j <= m; j++) {
        for (int i = 2; i <= n - 1; i++) {
            f[j][i] = f[j - 1][i + 1] + f[j - 1][i - 1];
        }
        f[j][1] = f[j - 1][2] + f[j - 1][n];
        f[j][n] = f[j - 1][1] + f[j - 1][n - 1];
    }
    cout << f[m][1] << endl;
    return 0;
}