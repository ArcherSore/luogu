#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int inf = 1e9;

struct Edge {
    int u, v, w;
    bool operator>(const Edge &other) const {
        return w > other.w;
    }
};

struct Dijkstra {
    int s;
    vector<vector<pii>> adj;
    vector<int> dist, vis;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    Dijkstra(int _n, int _s = 0) : s(_s) {
        init(_n);
    }

    void init(int n) {
        adj.resize(n);
        dist.assign(n, inf);
        vis.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void build() {
        dist[s] = 0;
        pq.push({dist[s], s});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = 1;
            for (auto &[v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    int query(int t) {
        return dist[t];
    }
};

struct DSU {
    vector<int> f;

    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
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
        f[y] = x;
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    Dijkstra dj(n);
    for (int i = 0; i < m; i++) {
        int u, v, l, a;
        cin >> u >> v >> l >> a;
        u--, v--;
        dj.addEdge(u, v, l);
        edges[i] = {u, v, a};
    }
    dj.build();
    sort(edges.begin(), edges.end(), greater<> ());

    int cnt = n;
    vector<vector<int>> adj(2 * n);
    vector<int> val(2 * n);
    DSU dsu(2 * n);
    for (auto &[u, v, w] : edges) {
        if (!dsu.same(u, v)) {
            adj[cnt].push_back(dsu.find(u));
            adj[cnt].push_back(dsu.find(v));
            dsu.merge(cnt, u);
            dsu.merge(cnt, v);
            val[cnt] = w;
            cnt++;
        }
    }
    adj.resize(cnt), val.resize(cnt);

    const int LOG = __lg(cnt) + 1;
    vector<vector<int>> parent(LOG, vector<int> (cnt, -1));
    vector<int> mr(cnt, inf); // the minimun distance of node u's subtree in Kruskal tree
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        parent[0][u] = fa;
        if (adj[u].empty()) {
            mr[u] = dj.query(u);
        }
        for (int v : adj[u]) {
            self(self, v, u);
            mr[u] = min(mr[u], mr[v]);
        }
    };
    dfs(dfs, cnt - 1, -1);
    for (int k = 0; k < LOG - 1; k++) {
        for (int u = 0; u < cnt; u++) {
            if (parent[k][u] != -1) {
                parent[k + 1][u] = parent[k][parent[k][u]];
            } else {
                parent[k + 1][u] = parent[k][u];
            }
        }
    }
    auto query = [&](int u, int limit) -> int {
        for (int i = LOG - 1; i >= 0; i--) {
            int nu = parent[i][u];
            if (nu != -1 && val[nu] > limit) {
                u = nu;
            }
        }
        return mr[u];
    };

    int q, k, s;
    cin >> q >> k >> s;
    int lastans = 0;
    while (q--) {
        int v, p;
        cin >> v >> p;
        v = (v + k * lastans - 1) % n + 1;
        v--;
        p = (p + k * lastans) % (s + 1);
        lastans = query(v, p);
        cout << lastans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}