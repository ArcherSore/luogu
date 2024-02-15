#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1005;
long long a[MAXN][MAXN];
long long dp[MAXN][MAXN][3]; // 右下上走到(i, j)的最大值

int main() {
    int n, m;
    cin >> n >> m;
    memset(dp, -0x7f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    // init
    for (int i = 0; i < 3; i++) {
        dp[1][1][i] = a[1][1];
    }
    for (int i = 2; i <= n; i++) {
        dp[i][1][1] = dp[i - 1][1][1] + a[i][1];
    }

    for (int j = 2; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            // 右
            dp[i][j][0] = max(dp[i][j - 1][0], max(dp[i][j - 1][1], dp[i][j - 1][2])) + a[i][j];
            if (i >= 2) // 下
                dp[i][j][1] = max(dp[i - 1][j][0], dp[i - 1][j][1]) + a[i][j];
        }
        for (int i = n - 1; i >= 1; i--) {
            // 上
            dp[i][j][2] = max(dp[i + 1][j][0], dp[i + 1][j][2]) + a[i][j];        
        }
    }

    cout << max(dp[n][m][0], max(dp[n][m][1], dp[n][m][2])) << endl;
    return 0;
}