#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int MAXN = 5e5 + 10;
int tr[MAXN];

int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int ask(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i)) {
        sum += tr[i];
    }
    return sum;
}

void solve() {
    cin >> n;
    vector<int> a(n + 1), x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        x[i] = a[i];
    }
    sort(x.begin() + 1, x.end());
    unique(x.begin() + 1, x.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(x.begin() + 1, x.end(), a[i]) - x.begin();
    }

    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (ask(n) - ask(a[i]));
        add(a[i], 1);
    }

    cout << ans << '\n';
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