#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

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
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    BIT fw(n);
    fw.add(0, v[0]);
    for (int i = 1; i < n; i++) {
        fw.add(i, v[i] - v[i - 1]);
    }
    while (m--) {
        int opt, x, y, k;
        cin >> opt >> x;
        if (opt == 1) {
            cin >> y >> k;
            x--, y--;
            fw.add(x, k);
            fw.add(y + 1, -k);
        } else {
            cout << fw.query(x) << '\n';
        }
    }

    return 0;
}