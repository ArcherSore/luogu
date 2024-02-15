#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 5e4 + 5;

int f1[MAXN][20], f2[MAXN][20];
int a[MAXN];
int n, q;

void init() {
    for (int i = 1; i <= n; i++) {
        f1[i][0] = f2[i][0] = a[i];
    }
    int t = log2(n);
    for (int j = 1; j <= t; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            f1[i][j] = max(f1[i][j - 1], f1[i + (1 << (j - 1))][j - 1]);
            f2[i][j] = min(f2[i][j - 1], f2[i + (1 << (j - 1))][j - 1]);
        }
    }
    return;
}

void ST_query(int l, int r) {
    int k = log2(r - l + 1);
    int mx = max(f1[l][k], f1[r - (1 << k) + 1][k]);
    int mn = min(f2[l][k], f2[r - (1 << k) + 1][k]);
    cout << mx - mn << '\n';
    return;
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init();

    while (q--) {
        int l, r;
        cin >> l >> r;
        ST_query(l, r);
    }
    return 0;
}