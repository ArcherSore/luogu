#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using LD = long double;
using PII = pair<int, int>;

const LD rate = (sqrtl(5.0L) + 1.0L) / 2.0L;

void solve() {
    int x, y;
    cin >> x >> y;
    if (x > y) {
        swap(x, y);
    }
    if (x != (int)((y - x) * rate)) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
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