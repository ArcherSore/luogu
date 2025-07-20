#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 5e5;

void solve() {
    int n, m;
    cin >> n >> m;
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

    vector<PII> sortlist(n);
    vector<int> listindex(n);
    for (int i = 0; i < n; i++) {
        sortlist[i] = {v[i], i};
    }
    sort(sortlist.begin(), sortlist.end());
    for (int i = 0; i < n; i++) {
        listindex[sortlist[i].second] = i;
    }

    vector<vector<int>> mode(bnum, vector<int> (bnum));
    vector<int> vcnt(N);
    for (int i = 0; i < bnum; i++) {
        for (int j = i; j < bnum; j++) {
            int cnt = (j> i ? mode[i][j - 1] : 0);
            for (int k = bl[j]; k <= br[j]; k++) {
                cnt = max(cnt, ++vcnt[v[k]]);
            }
            mode[i][j] = cnt;
        }
        for (int j = 0; j < n; j++) {
            vcnt[j] = 0;
        }
    }

    auto query = [&](int l, int r) -> int {
        int cnt = 0;
        if (bi[l] == bi[r]) {
            for (int i = l; i <= r; i++) {
                cnt = max(cnt, ++vcnt[v[i]]);
            }
            for (int i = l; i <= r; i++) {
                vcnt[v[i]] = 0;
            }
        } else {
            cnt = mode[bi[l] + 1][bi[r] - 1];
            for (int i = l; i <= br[bi[l]]; i++) {
                int idx = listindex[i];
                while (idx + cnt < n && sortlist[idx + cnt].first == v[i] && sortlist[idx + cnt].second <= r) {
                    cnt++;
                }
            }
            for (int i = bl[bi[r]]; i <= r; i++) {
                int idx = listindex[i];
                while (idx - cnt >= 0 && sortlist[idx - cnt].first == v[i] && sortlist[idx - cnt].second >= l) {
                    cnt++;
                }
            }
        }
        return cnt;
    };

    int res = 0;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l ^= res, r ^= res;
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