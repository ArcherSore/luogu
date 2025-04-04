#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int INF = 2e9;

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
    int add;
    Tag() : add(0) {}
    Tag(int x) : add(x) {}
    void apply(const Tag &t) & {
        add += t.add;
    }
};

struct Info {
    int mx, mn;
    int lmax, rmax;
    Info() : mx(0), mn(INF), lmax(0), rmax(0) {}
    Info(int x) : mx(x), mn(x), lmax(0), rmax(0) {}
    void apply(const Tag &t) & {
        mx += t.add;
        mn += t.add;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    c.mn = min(a.mn, b.mn);
    c.lmax = max({a.lmax, b.lmax, b.mx - a.mn});
    c.rmax = max({a.rmax, b.rmax, a.mx - b.mn});
    return c;
}

const int N = 5e4 + 1;
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

int query(int a, int b, LazySegmentTree<Info, Tag> &seg) {
    Info l, r;
    while (top[a] != top[b]) {
        if (depth[top[a]] <= depth[top[b]]) {
            r = seg.rangeQuery(dfn[top[b]], dfn[b] + 1) + r;
            b = father[top[b]];
        } else {
            l = seg.rangeQuery(dfn[top[a]], dfn[a] + 1) + l;
            a = father[top[a]];
        }
    }
    if (dfn[a] <= dfn[b]) {
        r = seg.rangeQuery(dfn[a], dfn[b] + 1) + r;
    } else {
        l = seg.rangeQuery(dfn[b], dfn[a] + 1) + l;
    }

    int res = max({0, l.rmax, r.lmax, r.mx - l.mn});
    return res;
}

void update(int a, int b, int v, LazySegmentTree<Info, Tag> &seg) {
    while (top[a] != top[b]) {
        if (depth[top[a]] <= depth[top[b]]) {
            seg.rangeApply(dfn[top[b]], dfn[b] + 1, Tag(v));
            b = father[top[b]];
        } else {
            seg.rangeApply(dfn[top[a]], dfn[a] + 1, Tag(v));
            a = father[top[a]];
        }
    }
    if (dfn[a] <= dfn[b]) {
        seg.rangeApply(dfn[a], dfn[b] + 1, Tag(v));
    } else {
        seg.rangeApply(dfn[b], dfn[a] + 1, Tag(v));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs1(0, -1);
    dfs2(0, 0);

    vector<int> ww(n);
    for (int i = 0; i < n; i++) {
        ww[dfn[i]] = w[i];
    }

    LazySegmentTree<Info, Tag> seg(ww);

    int q;
    cin >> q;
    while (q--) {
        int a, b, v;
        cin >> a >> b >> v;
        a--, b--;

        int res = query(a, b, seg);
        update(a, b, v, seg);

        cout << res << '\n';
    }

    return 0;
}