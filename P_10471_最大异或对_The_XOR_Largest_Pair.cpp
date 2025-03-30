#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int MAXN = 3200010;
int tr[MAXN][2];
int tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 31; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (tr[p][c] == 0) {
            tr[p][c] = ++tot;
        }
        p = tr[p][c];
    }
}

int search(int x) {
    int p = 1, res = 0;
    for (int i = 31; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (tr[p][1 - c] != 0) {
            res |= (1 << i);
            p = tr[p][1 - c];
        } else {
            p = tr[p][c];
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        insert(x);
    }

    int res = 0;
    for (auto x : a) {
        res = max(res, search(x));
    }
    cout << res;
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