#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;
int dp[MAXN][MAXN][2];

int main() {
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1, a; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a;
            dp[i][j][1 - a] = 0;
            dp[i][j][a] = min(dp[i - 1][j - 1][a], min(dp[i - 1][j][1 - a], dp[i][j - 1][1 - a])) + 1;
            ans = max(ans, dp[i][j][a]);
        }
    }
    cout << ans << endl;
    return 0;
}