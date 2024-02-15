#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int f[MAXN] = {0};

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j <= i / 2; j++) {
            f[i] += f[j];
        }
    }
    cout << f[n] << endl;
    return 0;
}