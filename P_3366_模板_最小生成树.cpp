// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct Edge {
    int u, d;
    bool operator<(const Edge &other) const {
        return d > other.d;
    }
};

int n, m;
vector<PII> G[5010];

void prim() {
    int res = 0, cnt = 0;
    vector<int> dis(n + 1, 0x3f3f3f3f);
    priority_queue<Edge> q;
    vector<int> vis(n + 1);
    dis[1] = 0;
    q.push({1, 0});
    while (!q.empty()) {
        if (cnt >= n) {
            break;
        }
        int u = q.top().u, d = q.top().d;
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        cnt++, res += d;
        for (auto [v, w] : G[u]) {
            if (w < dis[v]) {
                dis[v] = w;
                q.push({v, w});
            }
        }
    }
    if (cnt < n) {
        cout << "orz\n";
    } else {
        cout << res << '\n';
    }
}

void solve() {
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
    prim();
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