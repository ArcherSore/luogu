#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void solve() {
    int n, c, m;
    cin >> n >> c >> m;
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
        x--;
    }

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;
    vector<int> bi(n), bl(bnum), br(bnum);
    for (int i = 0; i < n; i++) {
        bi[i] = i / blen;
    }
    for (int i = 0; i < bnum; i++) {
        bl[i] = i * blen;
        br[i] = min(n - 1, (i + 1) * blen - 1);
    }

    vector<vector<int>> freq(bnum, vector<int> (c));
    for (int i = 0; i < bnum; i++) {
        for (int j = bl[i]; j <= br[i]; j++) {
            freq[i][v[j]]++;
        }
        if (i) {
            for (int j = 0; j < c; j++) {
                freq[i][j] += freq[i - 1][j];
            }
        }
    }
    vector<int> numcnt(c);
    vector<vector<int>> even(bnum, vector<int> (bnum));
    for (int i = 0; i < bnum; i++) {
        for (int j = i; j < bnum; j++) {
            even[i][j] = (i < j ? even[i][j - 1] : 0);
            for (int k = bl[j]; k <= br[j]; k++) {
                numcnt[v[k]]++;
                if (numcnt[v[k]] % 2 && numcnt[v[k]] != 1) {
                    even[i][j]--;
                } else if (numcnt[v[k]] % 2 == 0) {
                    even[i][j]++;
                }
            }
        }
        fill(numcnt.begin(), numcnt.end(), 0);
    }

    auto query = [&](int l, int r) -> int {
        int cnt = 0;
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                numcnt[v[i]]++;
                if (numcnt[v[i]] % 2 && numcnt[v[i]] != 1) {
                    cnt--;
                } else if (numcnt[v[i]] % 2 == 0) {
                    cnt++;
                }
            }
            for (int i = l; i <= r; i++) {
                numcnt[v[i]] = 0;
            }
        } else {
            cnt = even[bi[l] + 1][bi[r] - 1];
            for (int i = l; i <= br[bi[l]]; i++) {
                numcnt[v[i]]++;
                int tcnt = (bi[l] + 1 <= bi[r] - 1 ? freq[bi[r] - 1][v[i]] - freq[bi[l]][v[i]] : 0);
                if ((numcnt[v[i]] + tcnt) % 2 && (numcnt[v[i]] + tcnt) != 1) {
                    cnt--;
                } else if ((numcnt[v[i]] + tcnt) % 2 == 0) {
                    cnt++;
                }
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                numcnt[v[i]]++;
                int tcnt = (bi[l] + 1 <= bi[r] - 1 ? freq[bi[r] - 1][v[i]] - freq[bi[l]][v[i]] : 0);
                if ((numcnt[v[i]] + tcnt) % 2 && (numcnt[v[i]] + tcnt) != 1) {
                    cnt--;
                } else if ((numcnt[v[i]] + tcnt) % 2 == 0) {
                    cnt++;
                }
            }
            for (int i = l; i <= br[bi[l]]; i++) {
                numcnt[v[i]] = 0;
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                numcnt[v[i]] = 0;
            }
        }

        return cnt;
    };

    int res = 0;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l = (l + res) % n + 1;
        r = (r + res) % n + 1;
        if (l > r) {
            swap(l, r);
        }
        l--, r--;
        res = query(l, r);
        cout << res << '\n';
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