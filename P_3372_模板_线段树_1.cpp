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

struct Node {
    int l, r;
    LL sum, add;
} tr[4 * MAXN];

int n, m;
vector<int> w(MAXN);

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add;
        left.sum += 1LL * (left.r - left.l + 1) * root.add;
        right.add += root.add;
        right.sum += 1LL * (right.r - right.l + 1) * root.add;
        root.add = 0; 
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0};
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) {
            modify(u << 1, l, r, d);
        }
        if (r > mid) {
            modify(u << 1 | 1, l, r, d);
        }
        pushup(u);
    }
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if (l <= mid) {
        sum += query(u << 1, l, r);
    }
    if (r > mid) {
        sum += query(u << 1 | 1, l, r);
    }
    return sum;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);

    while (m--) {
        int opt, l, r, d;
        cin >> opt >> l >> r;
        if (opt == 1) {
            cin >> d;
            modify(1, l, r, d);
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