#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int f[MAXN] = {0};

int main() {
    int n;
    cin >> n;

    f[1] = 2;
    for (int i = 1; i <= n; i++) {
        f[i] = 2 * f[i - 1] + 2;
    }
    cout << f[n] << endl;
    return 0;
}