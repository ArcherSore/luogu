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
    if (count(v.begin(), v.end(), 1) == n) {
        if (n % 2) {
            cout << "Brother\n";
        } else {
            cout << "John\n";
        }
        return;
    }
    int t = 0;
    for (auto x : v) {
        t ^= x;
    }
    if (t) {
        cout << "John\n";
    } else {
        cout << "Brother\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}