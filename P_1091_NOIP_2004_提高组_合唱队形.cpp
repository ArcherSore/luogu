#include <bits/stdc++.h>
using namespace std;

int h[105];
int f[105], g[105];
int len[105];

int binary_search(int n, int x) {
    int l = 0, r = n, mid;
    while (l < r) {
        mid = (l + r + 1) / 2;
        if (x > len[mid]) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    int len1 = 0;
    len[0] = -1;
    for (int i = 1; i <= n; i++) {
        f[i] = binary_search(len1, h[i]) + 1;
        len[f[i]] = h[i];
        if (f[i] > len1) {
            len1 = f[i];
        }
    }

    int len2 = 0;
    memset(len, 0, sizeof(len));
    len[0] = -1;
    for (int i = n; i >= 1; i--) {
        g[i] = binary_search(len2, h[i]) + 1;
        len[g[i]] = h[i];
        if (g[i] > len2) {
            len2 = g[i];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(f[i] + g[i] - 1, ans);
    }
    cout << n - ans << endl;
    return 0;
}