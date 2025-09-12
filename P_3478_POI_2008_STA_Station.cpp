#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> siz(n), sum(n);
    auto dfs1 = [&](auto &&self, int u, int p) -> void {
        siz[u] = 1;
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            siz[u] += siz[v];
            sum[u] += sum[v] + siz[v];
        }
    };
    dfs1(dfs1, 0, -1);
    
    vector<ll> dp(n);
    dp[0] = sum[0];
    auto dfs2 = [&](auto &&self, int u, int p) -> void {
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            dp[v] = dp[u] - siz[v] + (n - siz[v]);
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, -1);

    ll mx = 0;
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > mx) {
            mx = dp[i];
            best = i + 1;
        }
    }
    cout << best;
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