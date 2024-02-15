#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int a[MAXN], b[MAXN], c[MAXN], tmp[3 * MAXN], d[3 * MAXN], num[MAXN];

void discrete(int n) {
    int cnt = 0;
    sort(tmp + 1, tmp + n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == 1 || tmp[i] != tmp[i - 1])
            d[++cnt] = tmp[i];
    }
    d[0] = cnt; // num of languages
}

int query(int x) {
    return lower_bound(d + 1, d + d[0] + 1, x) - d;
}

int main() {
    int n, m;
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tmp[++cnt] = a[i];
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
        tmp[++cnt] = b[i];
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &c[i]);
        tmp[++cnt] = c[i];
    }

    discrete(cnt);

    // statistic
    for (int i = 1; i <= n; i++) {
        num[query(a[i])]++;
    }
    int ans, t1 = 0, t2 = 0;
    for (int i = 1; i <= m; i++) {
        int most_satisfied = num[query(b[i])], satisfied = num[query(c[i])];
        if (most_satisfied > t1 || (most_satisfied == t1 && satisfied > t2)) {
            ans = i;
            t1 = most_satisfied;
            t2 = satisfied;
        }
    }
    cout << ans << endl;
    return 0;
}