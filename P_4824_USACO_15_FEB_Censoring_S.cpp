#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

vector<int> kmp(string &s) {
    int n = s.size();
    vector<int> f(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        j += (s[i] == s[j]);
        f[i + 1] = j;
    }
    return f;
}

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> f = kmp(t);
    stack<PII> st;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != t[j]) {
            j = f[j];
        }
        if (s[i] == t[j]) {
            st.push({i, j});
            j++;
        } else {
            st.push({i, -1});
        }
        if (j == m) {
            int c = m;
            while (c--) {
                st.pop();
            }
            j = (st.empty() ? 0 : st.top().second + 1);
        }
    }
    string res;
    while (!st.empty()) {
        res.push_back(s[st.top().first]);
        st.pop();
    }
    reverse(res.begin(), res.end());
    cout << res << '\n';
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