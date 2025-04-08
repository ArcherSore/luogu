#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct BIT {
    int n;
    vector<int> a;
    BIT(int _n) {
        init(_n);   
    }
    void init(int _n) {
        n = _n;
        a.assign(n, 0);
    }
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    int sum(int l, int r) {
        return query(r) - query(l);
    }
};

struct Query {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (auto &x : a) {
        x = lower_bound(b.begin(), b.end(), x) - b.begin();
    }

    int q;
    cin >> q;
    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qs[i] = {l, r, i};
    }
    sort(qs.begin(), qs.end(), [](const Query &a, const Query &b) {
        return a.r < b.r;
    });

    int p = 0;
    BIT fw(n);
    vector<int> ri(n, -1);
    vector<int> res(q);
    for (auto &[l, r, i] : qs) {
        while (p <= r) {
            if (ri[a[p]] != -1) {
                fw.add(ri[a[p]], -1);
            }
            ri[a[p]] = p;
            fw.add(ri[a[p]], 1);
            p++;
        }
        res[i] = fw.sum(l, r + 1);
    }

    for (auto x : res) {
        cout << x << '\n';
    }

    return 0;
}