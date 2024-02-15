#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int f[MAXN] = {0};

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        for (int x = 1; x <= i; x++) {
            f[i] += f[x - 1] * f[i - x];
        }
    }
    cout << f[n] << endl;
    return 0;
}