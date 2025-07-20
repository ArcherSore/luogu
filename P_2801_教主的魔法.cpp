#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }
    auto sv = v;

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;
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

    vector<int> lazy(bnum); // how much is added on block i
    auto update = [&](int l, int r, int x) -> void {
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                v[i] += x;
            }
            for (int i = bl[bi[l]]; i <= br[bi[l]]; i++) {
                sv[i] = v[i];
            }
            sort(sv.begin() + bl[bi[l]], sv.begin() + br[bi[l]] + 1);
        } else {
            for (int i = l; i <= br[bi[l]]; i++) {
                v[i] += x;
            }
            for (int i = bl[bi[l]]; i <= br[bi[l]]; i++) {
                sv[i] = v[i];
            }
            sort(sv.begin() + bl[bi[l]], sv.begin() + br[bi[l]] + 1);

            for (int i = bl[bi[r]]; i <= r; i++) {
                v[i] += x;
            }
            for (int i = bl[bi[r]]; i <= br[bi[r]]; i++) {
                sv[i] = v[i];
            }
            sort(sv.begin() + bl[bi[r]], sv.begin() + br[bi[r]] + 1);

            for (int i = bi[l] + 1; i < bi[r]; i++) {
                lazy[i] += x;
            }
        }
    };
    auto query = [&](int l, int r, int x) -> int {
        int cnt = 0;
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                if (v[i] + lazy[bi[i]] >= x) {
                    cnt++;
                }
            }
        } else {
            for (int i = l; i <= br[bi[l]]; i++) {
                if (v[i] + lazy[bi[i]] >= x) {
                    cnt++;
                }
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                if (v[i] + lazy[bi[i]] >= x) {
                    cnt++;
                }
            }
            for (int i = bi[l] + 1; i < bi[r]; i++) {
                int it = lower_bound(sv.begin() + bl[i], sv.begin() + br[i] + 1, x - lazy[i]) - (sv.begin() + bl[i]);
                cnt += blen - it;
            }
        }
        return cnt;
    };

    while (q--) {
        char opt;
        int a, b, c;
        cin >> opt;
        if (opt == 'A') {
            cin >> a >> b >> c;
            a--, b--;
            cout << query(a, b, c) << '\n';
        } else {
            cin >> a >> b >> c;
            a--, b--;
            update(a, b, c);
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