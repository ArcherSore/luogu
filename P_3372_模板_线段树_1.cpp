#include <iostream>
using namespace std;

using LL = long long;

const int N = 1e5 + 10;

int n, m;
int w[N];
struct Tree {
    int l, r;
    LL sum, add;
} tr[4 * N];

void pushup(int u) {
    tr[u].sum = tr[2 * u].sum + tr[2 * u + 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[2 * u], &right = tr[2 * u + 1];
    if (root.add) {
        left.add += root.add;
        left.sum += 1LL * root.add * (left.r - left.l + 1);
        right.add += root.add;
        right.sum += 1LL * root.add * (right.r - right.l + 1);
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0};
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += 1LL * k * (tr[u].r - tr[u].l + 1);
        tr[u].add += k; // !!!!!!!!!!!!!
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) {
            modify(2 * u, l, r, k);
        }
        if (r > mid) { // !!!!!!!!!!
            modify(2 * u + 1, l, r, k);
        }
        pushup(u);
    }
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        LL sum = 0;
        if (l <= mid) {
            sum += query(2 * u, l, r);
        }
        if (r > mid) {
            sum += query(2 * u + 1, l, r);
        }
        return sum;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);
    while (m--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> k;
            modify(1, l, r, k);
        } else {
            cout << query(1, l, r) << '\n';
        }
    }
    return 0;
}