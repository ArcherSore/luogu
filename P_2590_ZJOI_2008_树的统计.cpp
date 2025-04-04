#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int INF = 1e9;

template<class Info>
struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Info {
    LL mx, sum;
    Info() : mx(-INF), sum(0) {}
    Info(LL x) : mx(x), sum(x) {}
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    c.sum = a.sum + b.sum;
    return c;
}

const int N = 3e4;
vector<int> father(N + 1), depth(N + 1), siz(N + 1), son(N + 1, -1);
vector<int> dfn(N + 1), top(N + 1);
int cntd = 0;
vector<vector<int>> adj(N + 1);

void dfs1(int u, int fa) {
    father[u] = fa;
    siz[u] = 1;
    for (auto v : adj[u]) {
        if (v == fa) {
            continue;
        }
        depth[v] = depth[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
    }
    for (auto v : adj[u]) {
        if (v == fa) {
            continue;
        }
        if (son[u] == -1 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = cntd++;
    if (son[u] == -1) {
        return;
    }
    dfs2(son[u], t);
    for (auto v : adj[u]) {
        if (v == son[u] || v == father[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, 0);
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[dfn[i]];
    }
    SegmentTree<Info> seg(w);
    int q;
    cin >> q;
    while (q--) {
        string opt;
        int x, y;
        cin >> opt >> x >> y;
        if (opt == "CHANGE") {
            x--;
            seg.modify(dfn[x], Info(y));
        } else if (opt == "QMAX") {
            x--, y--;
            LL res = -INF;
            while (top[x] != top[y]) {
                if (depth[top[x]] <= depth[top[y]]) {
                    res = max(res, seg.rangeQuery(dfn[top[y]], dfn[y] + 1).mx);
                    y = father[top[y]];
                } else {
                    res = max(res, seg.rangeQuery(dfn[top[x]], dfn[x] + 1).mx);
                    x = father[top[x]];
                }
            }
            res = max(res, seg.rangeQuery(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1).mx);
            cout << res << '\n';
        } else {
            x--, y--;
            LL res = 0;
            while (top[x] != top[y]) {
                if (depth[top[x]] <= depth[top[y]]) {
                    res += seg.rangeQuery(dfn[top[y]], dfn[y] + 1).sum;
                    y = father[top[y]];
                } else {
                    res += seg.rangeQuery(dfn[top[x]], dfn[x] + 1).sum;
                    x = father[top[x]];
                }
            }
            res += seg.rangeQuery(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1).sum;
            cout << res << '\n';
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