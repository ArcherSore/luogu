#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int INF = 1e9;

struct DSU {
    vector<int> f, siz;
    vector<int> id;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        id.resize(n);
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

    void label() {
        unordered_map<int, int> mp;
        int cnt = 0;
        for (int i = 0; i < f.size(); i++) {
            int rep = find(i);
            if (mp.find(rep) == mp.end()) {
                mp[rep] = cnt++;
            }
            id[i] = mp[rep];
        }
    }
};

struct Kruskal {
    struct Edge {
        int u, v, w;
        Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
        bool operator<(const Edge &other) const {
            return w < other.w;
        }
    };

    int n;
    vector<Edge> edges;
    vector<vector<PII>> adj; // 最大生成树（森林）
    DSU dsu;

    Kruskal(int n): n(n) {
        adj.resize(n);
        dsu.init(n);
    }

    void add(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
    }

    void MST() {
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.w > b.w;
        });
        for (auto &e : edges) {
            if (dsu.merge(e.u, e.v)) {
                adj[e.u].push_back({e.v, e.w});
                adj[e.v].push_back({e.u, e.w});
            }
        }
    }
};

struct Tree {
    int n, LOG;
    vector<vector<int>> parent;
    vector<vector<int>> minVal;
    vector<int> depth;
    vector<vector<PII>> adj;

    Tree(int n) : n(n) {
        LOG = __lg(n) + 1;
        parent.assign(LOG, vector<int>(n, -1));
        minVal.assign(LOG, vector<int>(n, INF));
        depth.assign(n, 0);
        adj.resize(n);
    }

    void add(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs(int u, int p, int w, vector<bool> &vis) {
        vis[u] = true;
        parent[0][u] = p;
        minVal[0][u] = (p == -1 ? INF : w);
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, w, vis);
        }
    }

    void init(int root = 0) {
        vector<bool> vis(n, false);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, INF, vis);
            }
        }
        for (int k = 0; k < LOG - 1; k++) {
            for (int u = 0; u < n; u++) {
                if (parent[k][u] == -1) {
                    parent[k + 1][u] = -1;
                    minVal[k + 1][u] = minVal[k][u];
                } else {
                    parent[k + 1][u] = parent[k][parent[k][u]];
                    minVal[k + 1][u] = min(minVal[k][u], minVal[k][parent[k][u]]);
                }
            }
        }
    }

    int getMin(int u, int v) {
        int ans = INF;
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (d & (1 << i)) {
                ans = min(ans, minVal[i][u]);
                u = parent[i][u];
            }
        }
        if (u == v) {
            return ans;
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[i][u] != parent[i][v]) {
                ans = min({ans, minVal[i][u], minVal[i][v]});
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        ans = min({ans, minVal[0][u], minVal[0][v]});
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Kruskal mst(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        mst.add(u, v, w);
    }
    mst.MST();
    mst.dsu.label();

    Tree tree(n);
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : mst.adj[u]) {
            if (u < v) {
                tree.add(u, v, w);
            }
        }
    }
    tree.init();

    // handle queries
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (!mst.dsu.same(u, v)) {
            cout << -1 << '\n';
        } else {
            cout << tree.getMin(u, v) << '\n';
        }
    }

    return 0;
}