#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Query {
    int l, r, id, bid;
    bool operator<(const Query &other) const {
        if (bid != other.bid) {
            return bid < other.bid;
        }
        return (bid & 1) ? (r > other.r) : (r < other.r);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &x : a) {
        cin >> x;
    } 
    b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    
    int q;
    cin >> q;
    int blen = max<int>(1, sqrt(n));
    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qs[i] = {l, r, i, l / blen};
    }
    sort(qs.begin(), qs.end());

    vector<int> cnt(b.size()), res(q);
    int l = 0, r = -1, kind = 0;
    auto add = [&](int x) -> void {
        if (++cnt[x] == 1) {
            kind++;
        }
    };
    auto del = [&](int x) -> void {
        if (--cnt[x] == 0) {
            kind--;
        }
    };
    for (auto &q : qs) {
        while (l > q.l) {
            add(a[--l]);
        }
        while (r < q.r) {
            add(a[++r]);
        }
        while (l < q.l) {
            del(a[l++]);
        }
        while (r > q.r) {
            del(a[r--]);
        }
        res[q.id] = kind;
    }
    for (int x : res) {
        cout << x << '\n';
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