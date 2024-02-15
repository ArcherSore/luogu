#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN], len[MAXN], f[MAXN];

int binary_search1(int n, int x) {
    int l = 0, r = n, mid;
    while (l < r) {
        mid = (l + r + 1) / 2;
        if (len[mid] >= x) l = mid;
        else r = mid - 1;
    }
    return l;
}

int binary_search2(int n, int x) {
    int l = 0, r = n, mid;
    while (l < r) {
        mid = (l + r + 1) / 2;
        if (len[mid] < x) l = mid;
        else r = mid - 1;
    }
    return l;
}

void output(int n, int i) {
    for (int i = 0; i <= n; i++) 
        cout << len[i] << " ";
    cout << f[i] << endl;
    return;
}

int main() {
    int n = 0, ans = 0;
    while (cin >> a[n++]); n -= 1;
    len[0] = INT32_MAX;
    for (int i = 0; i < n; i++) {
        f[i] = binary_search1(ans, a[i]) + 1; // ans 最长下降序列的长度
        len[f[i]] = a[i];
        if (f[i] > ans) 
            ans = f[i];
        // output(ans, i);
    }
    cout << ans << endl;

    memset(len, 0, sizeof(len));
    len[0] = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        f[i] = binary_search2(ans, a[i]) + 1;
        len[f[i]] = a[i];
        if (f[i] > ans) 
            ans = f[i];
        // output(ans, i);
    }
    cout << ans << endl;
    return 0;
}