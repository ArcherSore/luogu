#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

int mod;

template<class Info, class Tag>
struct LazysegTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazysegTree() : n(0) {}
    LazysegTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazysegTree(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
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
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};

struct Tag {
    LL add;
    Tag() : add(0) {}
    Tag(LL x) : add(x) {}
    void apply(const Tag &t) & {
        add = (add + t.add) % mod;
    }
};

struct Info {
    LL sum, len;
    Info() : sum(0), len(0) {}
    Info(LL x) : sum(x), len(1) {}
    void apply(const Tag &t) & {
        sum = (sum + t.add * len % mod) % mod;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = (a.sum + b.sum) % mod;
    c.len = a.len + b.len;
    return c;
}

const int N = 1e5;
vector<int> father(N), siz(N), depth(N), son(N, -1);
vector<int> top(N), dfn(N), seg(N);
int cntd = 0;
vector<vector<int>> adj(N);
int n, m, r;
vector<int> scr(N);

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
    dfn[u] = cntd;
    seg[cntd++] = u;
    if (son[u] == -1) {
        return;
    }
    dfs2(son[u], t);
    for (auto v : adj[u]) {
        if (v == father[u] || v == son[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> r >> mod;
    for (int i = 0; i < n; i++) {
        cin >> scr[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(r - 1, -1);
    dfs2(r - 1, r - 1);

    vector<LL> val(n);
    for (int i = 0; i < n; i++) {
        val[dfn[i]] = scr[i];
    }

    LazysegTree<Info, Tag> seg(val);
    while (m--) {
        int opt, x, y, z;
        cin >> opt;
        if (opt == 1) {
            cin >> x >> y >> z;
            x--, y--;

            while (top[x] != top[y]) {
                if (depth[top[x]] <= depth[top[y]]) {
                    seg.rangeApply(dfn[top[y]], dfn[y] + 1, z);
                    y = father[top[y]];
                } else {
                    seg.rangeApply(dfn[top[x]], dfn[x] + 1, z);
                    x = father[top[x]];
                }
            }
            seg.rangeApply(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1, z);
        } else if (opt == 2) {
            cin >> x >> y;
            x--, y--;

            LL sum = 0;
            while (top[x] != top[y]) {
                if (depth[top[x]] <= depth[top[y]]) {
                    sum = (sum + seg.rangeQuery(dfn[top[y]], dfn[y] + 1).sum) % mod;
                    y = father[top[y]];
                } else {
                    sum = (sum + seg.rangeQuery(dfn[top[x]], dfn[x] + 1).sum) % mod;
                    x = father[top[x]];
                }
            }
            sum = (sum + seg.rangeQuery(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1).sum) % mod;
            cout << sum << '\n';
        } else if (opt == 3) {
            cin >> x >> z;
            x--;
            seg.rangeApply(dfn[x], dfn[x] + siz[x], Tag(z));
        } else {
            cin >> x;
            x--;
            cout << seg.rangeQuery(dfn[x], dfn[x] + siz[x]).sum % mod << '\n';
        }
    }

    return 0;
}