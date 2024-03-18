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

void spfa(vector<vector<int>> &dis, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector dis(n + 1, vector<int> (n + 1, 0x3f3f3f3f));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        dis[a][b] = dis[b][a] = c;
    }

    spfa(dis, n);

    int res = 0x3f3f3f3f;
    vector mind(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // 在ｉ和ｊ之间放传送门
            mind = dis;
            mind[i][j] = mind[j][i] = 0;
            // 更新以i和j为中转点的最短路
            for (int x = 1; x <= n; x ++) {
                for (int y = 1; y <= n; y++) {
                    mind[x][y] = min(mind[x][y], mind[x][i] + mind[i][y]);
                }
            }
            for (int x = 1; x <= n; x ++) {
                for (int y = 1; y <= n; y++) {
                    mind[x][y] = min(mind[x][y], mind[x][j] + mind[j][y]);
                }
            }
            // 计算最短距离之和
            int tot = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = i + 1; j <= n; j++) {
                    tot += mind[i][j];
                }
            }
            res = min(res, tot);
        }
    }

    cout << res << '\n';

    return;
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