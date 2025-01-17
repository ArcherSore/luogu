#include <bits/stdc++.h>

using namespace std;

using LL = long long;

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
    LL add, change;
    bool update;
    void apply(const Tag &t) & {
        if (t.update) {
            update = true;
            change = t.change;
            add = t.add;
        } else {
            if (update) {
                change += t.add;
            } else {
                add += t.add;
            }
        }
    }
};

const LL INF = 1e18;

struct Info {
    LL mx;

    Info() : mx(-INF) {}
    Info(LL x) : mx(x) {}

    void apply(const Tag &t) & {
        if (t.update) {
            mx = t.change + t.add;
        } else {
            mx += t.add;
        }
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<LL> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    LazySegmentTree<Info, Tag> seg(v);

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        l--, r--;
        if (op == 1) {
            LL x;
            cin >> x;
            seg.rangeApply(l, r + 1, {0, x, true});
        } else if (op == 2) {
            LL x;
            cin >> x;
            seg.rangeApply(l, r + 1, {x, 0, false});
        } else {
            cout << seg.rangeQuery(l, r + 1).mx << '\n';
        }
    }
    return 0;
}