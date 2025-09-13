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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    int blen = max<int>(1, sqrt(n));
    vector<Query> qs(m);
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        l--, r--;
        qs[i] = {l, r, i, l / blen};
    }
    sort(qs.begin(), qs.end());

    vector<int> cnt(b.size()), freq(n + 1), res(m);
    int l = 0, r = -1;
    int mxf = 0;
    auto add = [&](int x) -> void {
        freq[cnt[x]]--;
        cnt[x]++;
        freq[cnt[x]]++;
        mxf = max(mxf, cnt[x]);
    };
    auto del = [&](int x) -> void {
        freq[cnt[x]]--;
        cnt[x]--;
        freq[cnt[x]]++;
        if (mxf && freq[mxf] == 0) {
            mxf--;
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
        res[q.idx] = -mxf;
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