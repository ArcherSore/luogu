#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const LL N = 1e15;

vector<LL> f;

void init() {
    f.push_back(1);
    f.push_back(2);
    for (int i = 2; f[i - 1] + f[i - 2] <= N; i++) {
        f.push_back(f[i - 1] + f[i - 2]);
    }
}

void solve() {
    LL n;
    cin >> n;

    while (n) {
        int it = lower_bound(f.begin(), f.end(), n) - f.begin();
        if (f[it] == n) {
            break;
        } else {
            n -= f[it - 1];
        }
    }
    cout << n << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    init();

    while (T--) {
        solve();
    }

    return 0;
}