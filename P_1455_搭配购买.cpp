#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
const int MAXW = 1e4 + 5;

int c[MAXN], d[MAXN];
int dp[MAXW] = {0};
int fa[MAXN];

int find(int x) {
    if (fa[x] == x) 
        return x;
    return fa[x] = find(fa[x]);
}

int main() {
    int n, m, W;
    cin >> n >> m >> W;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> d[i];
        fa[i] = i;
    }
    
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        fa[find(a)] = find(b);
    }

    for (int i = 1; i <= n; i++) {
        if (fa[i] != i) {
            d[find(i)] += d[i];
            d[i] = 0;
            c[find(i)] += c[i];
            c[i] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        // cout << "w = " << w << ", v = " << v << endl;
        for (int j = W; j >= c[i]; j--) {
            dp[j] = max(dp[j], dp[j - c[i]] + d[i]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= W; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}