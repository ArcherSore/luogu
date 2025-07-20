#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }
    auto sv = v;

    // build block
    int blen = sqrt(n); // block size
    int bnum = (n + blen - 1) / blen; // block cnt
    vector<int> bi(n), bl(bnum), br(bnum);
    for (int i = 0; i < n; i++) {
        bi[i] = i / blen;
    }
    for (int i = 0; i < bnum; i++) {
        bl[i] = i * blen;
        br[i] = min((i + 1) * blen - 1, n - 1);
    }
    for (int i = 0; i < bnum; i++) {
        sort(sv.begin() + bl[i], sv.begin() + br[i] + 1);
    }

    // update
    auto update = [&](int i, int x) -> void {
        int l = bl[bi[i]], r = br[bi[i]];
        v[i] = x;
        for (int i = l; i <= r; i++) {
            sv[i] = v[i];
        }
        sort(sv.begin() + l, sv.begin() + r + 1);
    };
    // query
    auto query = [&](int l, int r, int x) -> int {
        int cnt = 0;
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                if (v[i] >= x) {
                    cnt++;
                }
            }
        } else {
            for (int i = l; i <= br[bi[l]]; i++) {
                if (v[i] >= x) {
                    cnt++;
                }
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                if (v[i] >= x) {
                    cnt++;
                }
            }
            for (int i = bi[l] + 1; i < bi[r]; i++) {
                int it = lower_bound(sv.begin() + bl[i], sv.begin() + br[i] + 1, x) - (sv.begin() + bl[i]);
                cnt += blen - it;
            }
        }
        return cnt;
    };

    int q;
    cin >> q;
    while (q--) {
        int opt, a, b, c;
        cin >> opt;
        if (opt == 1) {
            cin >> a >> b;
            a--;
            update(a, b);
        } else {
            cin >> a >> b >> c;
            a--, b--;
            cout << query(a, b, c) << endl;
        }
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