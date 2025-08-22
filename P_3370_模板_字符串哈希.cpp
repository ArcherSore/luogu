#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;
using u64 = unsigned long long;

const int base = 1e9 + 7;

int cv(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0' + 1;
    } else if ('A' <= c && c <= 'Z') {
        return c - 'A' + 11;
    } else {
        return c - 'a' + 37;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<u64> a(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            a[i] = a[i] * base + cv(s[j]);
        }
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    cout << a.size() << '\n';
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