#include <iostream>
using namespace std;

const int N = 1e5 + 10;

using LL = long long;

int n, q, m;
int w[N];
struct Node {
    int l, r;
    int sum, add, mul;
} tr[4 * N];

void exec(Node &u, int add, int mul) {
    u.add = (1LL * u.add * mul + add) % m;
    u.mul = 1LL * u.mul * mul % m;
    u.sum = (1LL * u.sum * mul + 1LL * add * (u.r - u.l + 1)) % m;
}

void pushup(int u) {
    tr[u].sum = (tr[2 * u].sum + tr[2 * u + 1].sum) % m;
}

void pushdown(int u) {
    exec(tr[2 * u], tr[u].add, tr[u].mul);
    exec(tr[2 * u + 1], tr[u].add, tr[u].mul);
    tr[u].add = 0, tr[u].mul = 1;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0, 1};
    } else {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int add, int mul) {
    if (tr[u].l >= l && tr[u].r <= r) {
        exec(tr[u], add, mul);
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) {
            modify(2 * u, l, r, add, mul);
        }
        if (r > mid) {
            modify(2 * u + 1, l, r, add, mul);
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
        sum += query(2 * u, l, r);
        sum %= m;
    }
    if (r > mid) {
        sum += query(2 * u + 1, l, r);
        sum %= m;
    }
    return sum;
} 

int main() {
    cin >> n >> q >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);
    while (q--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> k;
            modify(1, l, r, 0, k);
        } else if (op == 2) {
            cin >> k;
            modify(1, l, r, k, 1);
        } else {
            cout << query(1, l, r) << '\n';
        }
    }
    return 0;
}