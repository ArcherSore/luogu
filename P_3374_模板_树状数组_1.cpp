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

int n, m;
int tr[MAXN];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int query(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i)) {
        sum += tr[i];
    }
    return sum;
}

void solve() {
    cin >> n >> m;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        add(i, a);
    }

    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, k;
            cin >> x >> k;
            add(x, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(r) - query(l - 1) << '\n';
        }
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