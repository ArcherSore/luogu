#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Query {
    int l, r, idx, blk;
    bool operator<(const Query &o) const {
        if (blk != o.blk) {
            return blk < o.blk;
        }
        return (blk & 1) ? (r > o.r) : (r < o.r);
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    int blen = max<int>(1, sqrt(n));
    vector<Query> qs(m);
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        l--, r--;
        qs[i] = {l, r, i, l / blen};
    }
    sort(qs.begin(), qs.end());

    vector<ll> cnt(k), res(m);
    ll sum = 0;
    int l = 0, r = -1;
    auto add = [&](int x) -> void {
        sum = sum - cnt[x] * cnt[x] + (cnt[x] + 1) * (cnt[x] + 1);
        cnt[x]++;
    };
    auto del = [&](int x) -> void {
        sum = sum - cnt[x] * cnt[x] + (cnt[x] - 1) * (cnt[x] - 1);
        cnt[x]--;
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
        // cerr << l << ' ' << r << ' ' << q.idx << '\n';
        res[q.idx] = sum;
    }
    for (auto x : res) {
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