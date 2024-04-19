#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void manacher(string &s) {
    string t = "#";
    for (auto c : s) {
        t += c;
        t += '#';
    }
    int n = t.size(), res = 0;
    vector<int> d(n);
    for (int i = 0, j = 0; i < n; i++) {
        if (2 * j - i >= 0 && j + d[j] > i) {
            d[i] = min(d[2 * j - 1], j + d[j] - i);
        }
        while (i - d[i] >= 0 && i + d[i] < n && t[i - d[i]] == t[i + d[i]]) {
            d[i] += 1;
        }
        if (i + d[i] > j + d[j]) {
            j = i;
        }
        res = max(res, d[i]);
    }
    cout << res - 1 << '\n';
    return;
}

void solve() {
    string s;
    cin >> s;
    manacher(s);
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