#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        x--;
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[a[i]] = i;
    }
    vector<int> le(n, -1), ri(n, -1);
    auto build = [&]() -> void {
        stack<int> st;
        for (int i = 0; i < n; i++) {
            int pre = -1;
            while (!st.empty() && b[i] < b[st.top()]) {
                pre = st.top();
                st.pop();
            }
            if (!st.empty()) {
                ri[st.top()] = i;
            }
            if (pre != -1) {
                le[i] = pre;
            }
            st.push(i);
        }
    };
    build();
    auto dfs = [&](auto &&self, int u) -> void {
        cout << u + 1 << ' ';
        if (le[u] != -1) {
            self(self, le[u]);
        }
        if (ri[u] != -1) {
            self(self, ri[u]);
        }
    };
    dfs(dfs, a[0]);
    cout << '\n';
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