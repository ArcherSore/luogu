#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 1e5 + 5;

int f[MAXN][30], a[MAXN];
int n, q;

void init() {
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
    }
    int t = log2(n);
    for (int j = 1; j <= t; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    return;
}

int ST_query(int l, int r) {
    int t = log2(r - l + 1);
    return max(f[l][t], f[r - (1 << t) + 1][t]);
} 

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    init();
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", ST_query(l, r));
    }
    return 0;
}