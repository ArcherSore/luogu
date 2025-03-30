#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int BIT = 24;
const int MAXN = 6e5 + 10;
const int MAX_NODE = 25 * MAXN;

int trie[MAX_NODE][2];
int pass[MAX_NODE], root[MAXN];
int tot = 0;

int insert(int x, int preRt) {
    int newRt = ++tot;
    trie[newRt][0] = trie[preRt][0];
    trie[newRt][1] = trie[preRt][1];
    pass[newRt] = pass[preRt] + 1;

    int pre = newRt, cur;
    for (int i = BIT - 1; i >= 0; i--) {
        int c = (x >> i) & 1;
        preRt = trie[preRt][c];
        cur = ++tot;
        trie[cur][0] = trie[preRt][0];
        trie[cur][1] = trie[preRt][1];
        pass[cur] = pass[preRt] + 1;

        trie[pre][c] = cur;
        pre = cur;
    }
    return newRt;
}

int query(int x, int l, int r) {
    int res = 0;
    for (int i = BIT - 1; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (pass[trie[r][c ^ 1]] > pass[trie[l][c ^ 1]]) {
            res |= (1 << i);
            r = trie[r][c ^ 1];
            l = trie[l][c ^ 1];
        } else {
            r = trie[r][c];
            l = trie[l][c];
        }
    }
    return res;
}

void clear() {
    for (int i = 1; i <= tot; i++) {
        trie[i][0] = trie[i][1] = 0;
        pass[i] = 0;
    }
    tot = 0;
    memset(root, 0, sizeof(root));
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + m + 1), pre(n + m + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i];
        root[i] = insert(pre[i], root[i - 1]);
    }
    
    while (m--) {
        char opt;
        cin >> opt;
        if (opt == 'A') {
            int x;
            cin >> x;
            a[++n] = x;
            pre[n] = pre[n - 1] ^ a[n];
            root[n] = insert(pre[n], root[n - 1]);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            int res = query(x ^ pre[n], root[max(0, l - 2)], root[r - 1]);
            if (l == 1) {
                res = max(res, x ^ pre[n]);
            }
            cout << res << "\n";
        }
    }
    clear();
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