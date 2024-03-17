#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<LL, LL>;

void floyd(vector<vector<int>> &G, int n, int m) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] |= G[i][k] & G[k][j];    
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector G(n + 1, vector<int> (n + 1));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a][b] = 1;
    }

    floyd(G, n, m);

    int res = 0;
    for (int i = 1; i <= n; i++) {
        int state = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            state &= G[i][j] | G[j][i];
        }
        res += state;
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