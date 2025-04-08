#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct BIT {
    int n;
    vector<LL> a;
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
    LL query(int x) {
        LL res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    LL sum(int l, int r) {
        return query(r) - query(l);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    LL res = 0;
    BIT fw(n);
    for (int i = n - 1; i >= 0; i--) {
        res += fw.query(a[i]);
        fw.add(a[i], 1);
    }
    cout << res << '\n';
    
    return 0;
}