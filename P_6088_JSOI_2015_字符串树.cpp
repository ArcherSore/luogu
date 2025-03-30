#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct LCA {
    int n, LOG;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<vector<int>> adj;

    LCA(int n) : n(n) {
        LOG = __lg(n) + 1;
        parent.assign(n, vector<int> (LOG, -1));
        depth.assign(n, 0);
        adj.resize(n);
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        parent[u][0] = fa;
        for (int v : adj[u]) {
            if (v == fa) {
                continue;
            }
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void init() {
        dfs(0, -1);
        for (int k = 0; k < LOG - 1; k++) {
            for (int i = 0; i < n; i++) {
                if (parent[i][k] == -1) {
                    parent[i][k + 1] = parent[i][k];
                } else {
                    parent[i][k + 1] = parent[parent[i][k]][k];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if ((d >> i) & 1) {
                u = parent[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }
};

const int N = 1e5 + 10;
const int NODE = N * 10;
int trie[NODE][26];
int pass[NODE], root[N];
int tot = 0;

int insert(const string &s, int preRt) {
    int newRt = ++tot;
    for (int ch = 0; ch < 26; ch++) {
        trie[newRt][ch] = trie[preRt][ch];
    }
    pass[newRt] = pass[preRt] + 1;
    int pre = newRt, cur;
    for (int c : s) {
        c -= 'a';
        cur = ++tot;
        preRt = trie[preRt][c];
        for (int ch = 0; ch < 26; ch++) {
            trie[cur][ch] = trie[preRt][ch];
        }
        pass[cur] = pass[preRt] + 1;
        trie[pre][c] = cur;
        pre = cur;
    }
    return newRt;
}

int query(const string &s, int l, int r) {
    int cnt = N;
    for (int c : s) {
        c -= 'a';
        if (pass[trie[r][c]] <= pass[trie[l][c]]) {
            return 0;
        }
        // ????
        cnt = min(cnt, pass[trie[r][c]]);
        l = trie[l][c];
        r = trie[r][c];
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    LCA lca(n);
    vector<vector<pair<int, string>>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        u--, v--;
        lca.add(u, v);
        adj[u].push_back({v, s});
        adj[v].push_back({u, s});
    }
    lca.init();

    auto dfs = [&](auto &self, int u, int fa) -> void {
        for (auto [v, str] : adj[u]) {
            if (v == fa) {
                continue;
            }
            root[v + 1] = insert(str, root[u + 1]);
            self(self, v, u);
        }
    };
    
    root[1] = insert("", root[0]);
    dfs(dfs, 0, -1);

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        u--, v--;
        int rt = lca.lca(u, v);
        // cout << rt << ' ';
        int res = query(s, root[0], root[u + 1]) + query(s, root[0], root[v + 1]) - 2 * query(s, root[0], root[rt + 1]);
        cout << res << '\n';
    }

    return 0;
}