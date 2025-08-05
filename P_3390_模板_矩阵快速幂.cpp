#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const LL MOD = 1e9 + 7;

vector<vector<LL>> mul(const vector<vector<LL>> &a, const vector<vector<LL>> &b) {
    int n = a.size();
    vector<vector<LL>> c(n, vector<LL> (n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    return c;
}

vector<vector<LL>> fpow(vector<vector<LL>> A, LL k) {
    int n = A.size();
    vector<vector<LL>> res(n, vector<LL> (n));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    while (k) {
        if (k & 1) {
            res = mul(res, A);
        }
        A = mul(A, A);
        k >>= 1;
    }
    return res;
}

void solve() {
    LL n, k;
    cin >> n >> k;
    vector<vector<LL>> a(n, vector<LL> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    auto res = fpow(a, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << ' ';
        }
        cout << '\n';
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