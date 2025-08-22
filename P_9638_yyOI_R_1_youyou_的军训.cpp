#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Edge {
    int u, v, w, idx;
    bool operator>(const Edge &other) const {
        return w > other.w;
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
    
    // Find the representative of the set containing x
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    // Check if x and y are in the same set
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    // Attach y's representative to x's representative
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
    
    // Return the size of the set containing x.
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges[i] = {u, v, w, i};
    }
    sort(edges.begin(), edges.end(), greater<> ());

    int cnt = n;
    vector<vector<int>> adj(2 * n);
    vector<int> val(2 * n);
    vector<int> mp(m); // edge index to node index in Kruskal tree
    DSU dsu(2 * n);
    for (auto &[u, v, w, idx] : edges) {
        if (!dsu.same(u, v)) {
            adj[cnt].push_back(dsu.find(u));
            adj[cnt].push_back(dsu.find(v));
            dsu.merge(cnt, u);
            dsu.merge(cnt, v);
            val[cnt] = w;
            mp[idx] = cnt;
            cnt++;
        }
    }
    adj.resize(cnt), val.resize(cnt);

    const int LOG = __lg(cnt) + 1;
    vector<vector<int>> parent(LOG, vector<int> (cnt, -1));
    vector<int> leaf(cnt); // the leaf count in the subtree of node u
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        parent[0][u] = fa;
        if (adj[u].empty()) {
            leaf[u] = 1;
            return;
        }
        for (int v : adj[u]) {
            self(self, v, u);
            leaf[u] += leaf[v];
        }
    };
    for (int i = 0; i < cnt; i++) {
        if (dsu.find(i) == i) {
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

    int limit = -1;
    auto work = [&](int u) -> int {
        for (int i = LOG - 1; i >= 0; i--) {
            int nu = parent[i][u];
            if (nu != -1 && val[nu] >= limit) {
                u = nu;
            }
        }
        return leaf[u];
    };
    vector<pii> nval; // temporarily save changes, {idx in tree, new value}
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> limit;
            for (auto &[idx, nv] : nval) {
                val[idx] = nv;
            }
            nval.clear();
        } else if (op == 2) {
            int u;
            cin >> u;
            u--;
            cout << work(u) << '\n';
        } else {
            int x, y;
            cin >> x >> y;
            x--;
            nval.push_back({mp[x], y});
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