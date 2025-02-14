#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

struct Seg {
    int id;
    int l, r;
};

struct SparseTable {
    int n, maxlvl;
    vector<vector<int>> st;
    vector<Seg> seg;

    SparseTable(const vector<Seg> &v) {
        seg = v;
        init();
    }

    void init() {
        n = seg.size();
        maxlvl = __lg(n) + 1;
        st.assign(n, vector<int> (maxlvl));
        int p = 0;
        for (int i = 0; i < n; i++) {
            while (p + 1 < n && seg[p + 1].l <= seg[i].r) {
                p++;
            }
            st[i][0] = p;
        }
        for (int p = 1; p < maxlvl; p++) {
            for (int i = 0; i < n; i++) {
                st[i][p] = st[st[i][p - 1]][p - 1];
            }
        }
    }

    int query(int i, int m) {
        int aim = seg[i].l + m, cur = i;
        int ans = 1;
        for (int p = maxlvl - 1; p >= 0; p--) {
            int next = st[cur][p];
            if (seg[next].r < aim) {
                ans += (1 << p);
                cur = next;
            }
        }
        return ans + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Seg> seg(2 * n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (b < a) {
            b += m;
        }
        seg[i] = {i, a, b};
        seg[i + n] = {i, a + m, b + m};
    }
    sort(seg.begin(), seg.end(), [](const Seg &a, const Seg &b) {
        if (a.l != b.l) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });
    
    SparseTable st(seg);
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[seg[i].id] = st.query(i, m);
    }

    for (auto x : res) {
        cout << x << ' ';
    }

    return 0;
}