#include <iostream>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e6 + 10; // 
const LL INF = 1e18; // 表示没有全变为x

int n, q;
int w[N];
struct Node {
    int l, r;
    LL max, change, add;
} tr[4 * N];

void pushup(int u) {
    tr[u].max = max(tr[2 * u].max, tr[2 * u + 1].max);
}

void exec(Node &u, LL change, LL add) {
    if (change != INF) {
        u.add = 0;
        u.change = change;
        u.max = change;
    }
    if (add) {
        u.add += add;
        u.max += add;
    }
}

void pushdown(int u) {
    exec(tr[2 * u], tr[u].change, tr[u].add);
    exec(tr[2 * u + 1], tr[u].change, tr[u].add);
    tr[u].change = INF, tr[u].add = 0;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], INF, 0};
        return;
    }
    tr[u] = {l, r, -INF, INF, 0};
    int mid = l + r >> 1;
    build(2 * u, l, mid);
    build(2 * u + 1, mid + 1, r);
    pushup(u);
} // ok

void modify(int u, int l, int r, LL change, LL add) {
    if (tr[u].l >= l && tr[u].r <= r) {
        exec(tr[u], change, add);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) {
        modify(2 * u, l, r, change, add);
    }
    if (r > mid) {
        modify(2 * u + 1, l, r, change, add);
    }
    pushup(u);
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].max;
    }
    pushdown(u);
    LL sum = -INF;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) {
        sum = max(sum, query(2 * u, l, r));
    }
    if (r > mid) {
        sum = max(sum, query(2 * u + 1, l, r));
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);

    while (q--) {
        int opt, l, r, x;
        cin >> opt >> l >> r;
        if (opt == 1) {
            cin >> x;
            modify(1, l, r, x, 0); // 全变x
        } else if (opt == 2) {
            cin >> x;
            modify(1, l, r, INF, x); // 全加x
        } else {
            cout << query(1, l, r) << '\n';
        }
    }

    return 0;
}