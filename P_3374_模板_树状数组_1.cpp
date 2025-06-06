# include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> a;
    BIT(int _n) {
        init(_n);
    }
    void init(int _n) {
        n = _n;
        a.assign(n, 0);
    }
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    int sum(int l, int r) {
        return query(r) - query(l);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    BIT fw(n);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        fw.add(i, x);
    }
    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            fw.add(x - 1, y);
        } else {
            cout << fw.sum(x - 1, y) << '\n';
        }
    }

    return 0;
}