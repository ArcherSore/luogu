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
    vector<int> a(n), pre(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] ^ a[i];
    }

    int blen = max<int>(1, sqrt(n));
    vector<Query> qs(m);
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        qs[i] = {l - 1, r, i, (l - 1) / blen};
    }
    sort(qs.begin(), qs.end());

    vector<ll> cnt(1 << 18), res(m);
    int l = 0, r = -1;
    ll sum = 0;
    auto add = [&](int x) -> void {
        sum += cnt[x ^ k];
        cnt[x]++;
    };
    auto del = [&](int x) -> void {
        cnt[x]--;
        sum -= cnt[x ^ k];
    };
    for (auto &q : qs) {
        // update 1~l-1 ~ 1~r
        while (l > q.l) {
            add(pre[--l]);
        }
        while (r < q.r) {
            add(pre[++r]);
        }
        while (l < q.l) {
            del(pre[l++]);
        }
        while (r > q.r) {
            del(pre[r--]);
        }
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