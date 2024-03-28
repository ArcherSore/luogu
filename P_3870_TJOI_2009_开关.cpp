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

int n, m;
struct Node {
    int l, r;
    int num;
    int flag; // 懒标记
} tr[4 * MAXN];

void exec(int u) {
    tr[u].num = (tr[u].r - tr[u].l + 1) - tr[u].num;
}

void pushup(int u) {
    tr[u].num = tr[u << 1].num + tr[u << 1 | 1].num;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.flag) {
        exec(u << 1), exec(u << 1 | 1);
        left.flag ^= 1;
        right.flag ^= 1;
        root.flag = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, 0, 0};
    } else {
        tr[u] = {l, r, 0, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        exec(u);
        tr[u].flag ^= 1;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) {
            modify(u << 1, l, r);
        }
        if (r > mid) {
            modify(u << 1 | 1, l, r);
        }
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].num;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int sum = 0;
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

    build(1, 1, n);

    while (m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 0) {
            modify(1, l, r);
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