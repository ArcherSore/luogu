#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e6 + 5;
int a[MAXN] = {0}, d[MAXN] = {0}, e[MAXN] = {0};

int main() {
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        d[i] = a[i] - a[i - 1];
    }
    int l, r, z;
    while (p--) {
        scanf("%d%d%d", &l, &r, &z);
        d[l] += z;
        d[r + 1] -= z;
    }

    int minn = 100;
    for (int i = 1; i <= n; i++) {
        e[i] = e[i - 1] + d[i];
        minn = min(minn, e[i]);
    }
    cout << minn << endl;
    return 0;
}