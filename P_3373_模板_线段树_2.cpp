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

int n, m, p;
vector<int> w(MAXN);
struct Node {
    int l, r;
    int sum, add, mul;
} tr[4 * MAXN];

void excu(Node &root, int add, int mul) {
    root.sum = (1LL * root.sum * mul + 1LL * (root.r - root.l + 1) * add) % p;
    root.mul = (1LL * root.mul * mul) % p;
    root.add = (1LL * root.add * mul + add) % p;
}

void pushup(int u) {
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}

void pushdown(int u) {
    excu(tr[u << 1], tr[u].add, tr[u].mul);
    excu(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    tr[u].add = 0, tr[u].mul = 1;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0, 1};
    } else {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int add, int mul) {
    if (tr[u].l >= l && tr[u].r <= r) {
        excu(tr[u], add, mul);
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) {
            modify(u << 1, l, r, add, mul);
        }
        if (r > mid) {
            modify(u << 1 | 1, l, r, add, mul);
        }
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int sum = 0;
    if (l <= mid) {
        sum = (sum + query(u << 1, l, r)) % p;
    }
    if (r > mid) {
        sum = (sum + query(u << 1 | 1, l, r)) % p;
    }
    return sum;
}

void solve() {
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);

    while (m--) {
        int opt, l, r, c;
        cin >> opt >> l >> r;
        if (opt == 1) {
            cin >> c;
            modify(1, l, r, 0, c);
        } else if (opt == 2) {
            cin >> c;
            modify(1, l, r, c, 1);
        } else {
            cout << query(1, l, r) << '\n';
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