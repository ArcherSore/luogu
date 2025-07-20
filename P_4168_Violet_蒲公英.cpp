#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }
    auto dv = v;
    sort(dv.begin(), dv.end());
    dv.erase(unique(dv.begin(), dv.end()), dv.end());
    int sz = dv.size();
    for (int i = 0; i < n; i++) {
        v[i] = lower_bound(dv.begin(), dv.end(), v[i]) - dv.begin();
    }

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;
    vector<int> bi(n), bl(bnum), br(bnum);
    for (int i = 0; i < n; i++) {
        bi[i] = i / blen;
    }
    for (int i = 0; i < bnum; i++) {
        bl[i] = i * blen;
    }
    for (int i = 0; i < bnum; i++) {
        br[i] = min((i + 1) * blen - 1, n - 1);
    }

    vector<vector<int>> freq(bnum, vector<int> (sz));
    vector<vector<int>> mode(bnum, vector<int> (bnum));
    for (int i = 0; i < n; i++) {
        freq[bi[i]][v[i]]++;
    }
    for (int i = 1; i < bnum; i++) {
        for (int j = 0; j < sz; j++) {
            freq[i][j] += freq[i - 1][j];
        }
    }
    auto getcnt = [&](int i, int j, int x) -> int {
        if (i) {
            return freq[j][x] - freq[i - 1][x];
        } else {
            return freq[j][x];
        }
    };
    for (int i = 0; i < bnum; i++) {
        int best = 0;
        mode[i][i] = v[bl[i]];
        for (int j = bl[i]; j <= br[i]; j++) {
            int cur = getcnt(i, i, v[j]);
            if (cur > best || cur == best && v[j] < mode[i][i]) {
                mode[i][i] = v[j];
                best = cur;
            }
        }
    }
    for (int i = 0; i < bnum; i++) {
        for (int j = i + 1; j < bnum; j++) {
            int most = mode[i][j - 1];
            int best = getcnt(i, j, most);
            for (int k = bl[j]; k <= br[j]; k++) {
                int cur = getcnt(i, j, v[k]);
                if (cur > best || cur == best && v[k] < most) {
                    most = v[k];
                    best = cur;
                }
            }
            mode[i][j] = most;
        }
    }

    vector<int> mem(sz);
    auto query = [&](int l, int r) -> int {
        int most = -1, best = 0;
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                mem[v[i]]++;
                if (mem[v[i]] > best || mem[v[i]] == best && v[i] < most) {
                    best = mem[v[i]];
                    most = v[i];
                }
            }
            // clear
            for (int i = l; i <= r; i++) {
                mem[v[i]] = 0;
            }
        } else {
            for (int i = l; i <= br[bi[l]]; i++) {
                mem[v[i]]++;
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                mem[v[i]]++;
            }

            most = mode[bi[l] + 1][bi[r] - 1];
            best = getcnt(bi[l] + 1, bi[r] - 1, most) + mem[most];
            for (int i = l; i <= br[bi[l]]; i++) {
                int cur = getcnt(bi[l] + 1, bi[r] - 1, v[i]) + mem[v[i]];
                if (cur > best || cur == best && v[i] < most) {
                    most = v[i];
                    best = cur;
                }
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                int cur = getcnt(bi[l] + 1, bi[r] - 1, v[i]) + mem[v[i]];
                if (cur > best || cur == best && v[i] < most) {
                    most = v[i];
                    best = cur;
                }
            }
            // clear
            for (int i = l; i <= br[bi[l]]; i++) {
                mem[v[i]] = 0;
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                mem[v[i]] = 0;
            }
        }
        return dv[most];
    };

    int res = 0;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l = (l + res - 1) % n + 1;
        r = (r + res - 1) % n + 1;
        if (l > r) {
            swap(l, r);
        }
        l--, r--;
        
        res =  query(l, r);
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