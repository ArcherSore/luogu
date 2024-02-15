#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
    char opt;
    int x;
} node[105];

int dp[105][105][2]; // 0 : max 1 : min

int max(int i, int k, int j) {
    int d[2] = {0, 1};
    int res = -0x7fffffff;
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q++) {
            res = max(res, dp[i][k][p] * dp[k + 1][j][q]);
        }
    }
    return res;
}

int min(int i, int k, int j) {
    int d[2] = {0, 1};
    int res = 0x7fffffff;
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q++) {
            res = min(res, dp[i][k][p] * dp[k + 1][j][q]);
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    // init
    for (int i = 0; i < 105; i++) {
        for (int j = 0; j < 105; j++) {
            dp[i][j][0] = -0x7fffffff;
            dp[i][j][1] = 0x7fffffff;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> node[i].opt >> node[i].x;
        node[i + n].opt = node[i].opt;
        node[i + n].x = node[i].x;
        dp[i][i][0] = dp[i][i][1] = node[i].x;
        dp[i + n][i + n][0] = dp[i + n][i + n][1] = node[i + n].x;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= 2 * n - len + 1; i++) {
            int j = len + i - 1;
            for (int k = i; k < j; k++) {
                if (node[k + 1].opt == 't') {
                    dp[i][j][0] = max(dp[i][j][0], dp[i][k][0] + dp[k + 1][j][0]);
                    dp[i][j][1] = min(dp[i][j][1], dp[i][k][1] + dp[k + 1][j][1]);
                } else {
                    dp[i][j][0] = max(dp[i][j][0], max(i, k, j));
                    dp[i][j][1] = min(dp[i][j][1], min(i, k, j));
                }
            }
        }
    }

    int ans = -0x7fffffff;
    queue<int> res;
    for (int i = 1; i <= n; i++) {
        // cout << dp[i][i + n - 1][0] << endl;
        if (dp[i][i + n - 1][0] > ans) {
            ans = dp[i][i + n - 1][0];
            while (!res.empty()) {
                res.pop();
            }
        }
        if (dp[i][i + n - 1][0] == ans) res.push(i);
        ans = max(ans, dp[i][i + n - 1][0]);
    }
    cout << ans << endl;
    while (!res.empty()) {
        cout << res.front() << " ";
        res.pop();
    }
    return 0;
}