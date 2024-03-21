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

const int MAXN = 1e5 + 10;
const int MOD = 99999997;

struct Tic {
    int a, b;
    bool operator<(const Tic& other) const {
        return a < other.a;
    }
};

int n;
int tr[MAXN];

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

void discrete(vector<Tic> &t, int n) {
    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = t[i].a;
        y[i] = t[i].b;
    }
    sort(x.begin() + 1, x.end());
    sort(y.begin() + 1, y.end());
    for (int i = 1; i <= n; i++) {
        t[i].a = lower_bound(x.begin() + 1, x.end(), t[i].a) - x.begin();
        t[i].b = lower_bound(y.begin() + 1, y.end(), t[i].b) - y.begin();
    }
}

void solve() {
    cin >> n;
    vector<Tic> t(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i].a;
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i].b;
    }
    discrete(t, n);

    vector<int> mp(n + 1);
    for (int i = 1; i <= n; i++) {
        mp[t[i].a] = i;
    }
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        res += ask(n) - ask(mp[t[i].b]);
        res %= MOD;
        add(mp[t[i].b], 1);
    }

    cout << res << '\n';
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