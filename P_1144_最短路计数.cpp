#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<LL, LL>;

const int MOD = 100003;

void bfs(vector<vector<PII>> &G, int n, int m) {
    vector<int> vis(n + 1);
    vector<int> dis(n + 1, 0x3f3f3f3f);
    vector<int> cnt(n + 1);
    queue<int> q;
    dis[1] = 0;
    cnt[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (vis[x]) {
            continue;
        }
        vis[x] = 1;

        for (auto [y, w] : G[x]) {
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                cnt[y] = cnt[x];
                q.push(y);
            } else if (dis[y] == dis[x] + w) {
                cnt[y] = (cnt[y] + cnt[x]) % MOD;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << cnt[i] << '\n';
    }

    return;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back({b, 1});
        G[b].push_back({a, 1});
    }

    bfs(G, n, m);
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