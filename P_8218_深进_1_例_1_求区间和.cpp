#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN] = {0}, sum[MAXN] = {0};

int main() {
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = a[i] + sum[i - 1];
    }
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << endl;
    }
    return 0;
}