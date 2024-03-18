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
using PII = pair<LL, LL>;

void spfa(vector<vector<int>> &G, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> seg(m);
    for (int i = 0; i < m; i++) {
        cin >> seg[i];
    }
    vector G(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> G[i][j];
        }
    }

    spfa(G, n);

    LL res = 0;
    for (int i = 1; i < m; i++) {
        res += G[seg[i - 1]][seg[i]];
    }

    cout << res << '\n';

    return ;
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