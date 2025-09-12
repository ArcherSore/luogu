#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> c(n);
    for (int &x : c) {
        cin >> x;
    }

    vector<vector<int>> sum(n, vector<int> (k + 1));
    auto dfs1 = [&](auto &&self, int u, int p) -> void {
        sum[u][0] = c[u];
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            for (int t = 1; t <= k; t++) {
                sum[u][t] += sum[v][t - 1];
            }
        }
    };
    dfs1(dfs1, 0, -1);

    vector<vector<int>> dp(n, vector<int> (k + 1));
    dp[0] = sum[0];
    auto dfs2 = [&](auto &&self, int u, int p) -> void {
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            dp[v][0] = c[v];
            dp[v][1] = sum[v][1] + c[u];
            for (int t = 2; t <= k; t++) {
                dp[v][t] = sum[v][t] + dp[u][t - 1] - sum[v][t - 2];
            }
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, -1);

    // for (int i = 0; i < n; i++) {
    //     for (int t = 0; t <= k; t++) {
    //         cerr << dp[i][t] << ' ';
    //     }
    //     cerr << '\n';
    // }
    
    for (int i = 0; i < n; i++) {
        cout << accumulate(dp[i].begin(), dp[i].end(), 0LL) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}