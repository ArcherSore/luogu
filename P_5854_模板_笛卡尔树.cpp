#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }
    vector<int> le(n, -1), ri(n, -1);
    auto build = [&]() -> void {
        stack<int> st;
        for (int i = 0; i < n; i++) {
            int pre = -1;
            while (!st.empty() && v[i] < v[st.top()]) {
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
    ll res1 = 0, res2 = 0;
    for (ll i = 0; i < n; i++) {
        res1 ^= (i + 1) * (le[i] + 2);
        res2 ^= (i + 1) * (ri[i] + 2);
    }
    cout << res1 << ' ' << res2 << '\n';
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