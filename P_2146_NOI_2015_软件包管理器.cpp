#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(vector<T> init_) {
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
    int val;
    bool update;
    Tag() : val(0), update(false) {}
    Tag(int x) : val(x), update(true) {}
    void apply(const Tag &t) & {
        if (t.update) {
            val = t.val;
            update = true;
        }
    }
};

struct Info {
    int sum, len;
    Info() : sum(0), len(1) {}
    Info(int x) : sum(x), len(1) {}
    void apply(const Tag &t) & {
        if (t.update) {
            sum = t.val * len;
        }
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    return c;
}

const int N = 1e5 + 5;
vector<int> father(N), depth(N), siz(N), son(N, -1);
vector<int> dfn(N), top(N);
int cntd = 0;
vector<vector<int>> adj(N);

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
        if (v == father[u] || v == son[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int fa;
        cin >> fa;
        adj[fa].push_back(i);
    }
    dfs1(0, -1);
    dfs2(0, 0);

    LazySegmentTree<Info, Tag> seg(n);

    int q;
    cin >> q;
    while (q--) {
        string opt;
        int x;
        cin >> opt >> x;
        if (opt == "install") {
            int res = 0;
            while (top[x] != top[0]) {
                int chain_len = dfn[x] - dfn[top[x]] + 1;
                res += chain_len - seg.rangeQuery(dfn[top[x]], dfn[x] + 1).sum;
                seg.rangeApply(dfn[top[x]], dfn[x] + 1, Tag(1));
                x = father[top[x]];
            }
            int chain_len = dfn[x] - dfn[0] + 1;
            res += chain_len - seg.rangeQuery(0, dfn[x] + 1).sum;
            seg.rangeApply(0, dfn[x] + 1, Tag(1));
            cout << res << '\n';
        } else {
            cout << seg.rangeQuery(dfn[x], dfn[x] + siz[x]).sum << '\n';
            seg.rangeApply(dfn[x], dfn[x] + siz[x], Tag(0));
        }
    }
    return 0;
}