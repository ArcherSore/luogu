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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n + 1, vector<int> (m + 1));
    // init
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                G[i][j] = 0;
            } else {
                G[i][j] = 0x3f3f3f3f;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = G[b][a] = min(c, G[a][b]);
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (G[i][j] > G[i][k] + G[k][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << G[i][j] << " ";
        }
        cout << '\n';
    }
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