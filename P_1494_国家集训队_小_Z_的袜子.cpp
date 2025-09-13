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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        x--;
    }

    int blen = max<int>(1, sqrt(n));
    vector<Query> qs(q);
    for (int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        l--, r--;
        qs[i] = {l, r, i, l / blen};
    }
    sort(qs.begin(), qs.end());

    vector<ll> cnt(n);
    vector<ll> f(q), g(q);
    ll sum = 0;
    int l = 0, r = -1;
    auto add = [&](int x) -> void {
        sum = sum - cnt[x] * (cnt[x] - 1) / 2 + (cnt[x] + 1) * cnt[x] / 2;
        cnt[x]++;
    };
    auto del = [&](int x) -> void {
        sum = sum - cnt[x] * (cnt[x] - 1) / 2 + (cnt[x] - 1) * (cnt[x] - 2) / 2;
        cnt[x]--;
    };
    for (auto &q : qs) {
        // cerr << "OK\n";
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
        if (sum == 0) {
            f[q.idx] = 0;
            g[q.idx] = 1;
            continue;
        }
        // cerr << l << ' ' << r << '\n';
        ll len = q.r - q.l + 1;
        ll tot = len * (len - 1) / 2;
        // assert(gcd(sum, tot) > 0);
        f[q.idx] = sum / gcd(sum, tot);
        g[q.idx] = tot / gcd(sum, tot);
    }
    for (int i = 0; i < q; i++) {
        cout << f[i] << '/' << g[i] << '\n';
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