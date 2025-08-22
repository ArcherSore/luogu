#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back({u, v, w});
    }
    sort(edges.begin(), edges.end());

    int cnt = n; // the node count of Kruskal reconstruction tree
    vector<vector<int>> adj(2 * n);
    vector<int> val(2 * n);
    DSU dsu(2 * n);
    for (auto &e : edges) {
        if (!dsu.same(e.u, e.v)) {
            adj[cnt].push_back(dsu.find(e.u));
            adj[cnt].push_back(dsu.find(e.v));
            val[cnt] = e.w;
            dsu.merge(cnt, e.u);
            dsu.merge(cnt, e.v);
            cnt++;
        }
    }
    adj.resize(cnt), val.resize(cnt);

    const int LOG = __lg(cnt) + 1;
    vector<vector<int>> parent(LOG, vector<int> (cnt, -1));
    vector<int> depth(cnt);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        parent[0][u] = fa;
        for (int v : adj[u]) {
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };
    // handle forests
    for (int i = 0; i < cnt; i++) {
        if (dsu.find(i) == i) {
            // is the candidate of component
            dfs(dfs, i, -1);
        }
    }

    for (int k = 0; k < LOG - 1; k++) {
        for (int u = 0; u < cnt; u++) {
            if (parent[k][u] != -1) {
                parent[k + 1][u] = parent[k][parent[k][u]];
            } else {
                parent[k + 1][u] = -1;
            }
        }
    }
    auto lca = [&](int u, int v) -> int {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (d & (1 << i)) {
                u = parent[i][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[i][v] != parent[i][u]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    };

    // handle queries
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (dsu.same(u, v)) {
            cout << val[lca(u, v)] << '\n';
        } else {
            cout << "impossible\n";
        }
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