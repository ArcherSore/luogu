#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1005;
const int MOD = 19650827;

int dp[MAXN][MAXN][2]; // 0 左 1 右

int main() {
    int n;
    cin >> n;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        dp[i][i][0] = 1; // 默认从左进 不然一人的时候方案数为2了！！！
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            if (h[i] < h[i + 1]) dp[i][j][0] += dp[i + 1][j][0];
            if (h[i] < h[j]) dp[i][j][0] += dp[i + 1][j][1];
            if (h[j] > h[j - 1]) dp[i][j][1] += dp[i][j - 1][1];
            if (h[j] > h[i]) dp[i][j][1] += dp[i][j - 1][0];
            dp[i][j][0] %= MOD;
            dp[i][j][1] %= MOD;
        }
    }
    cout << (dp[1][n][0] + dp[1][n][1]) % MOD << endl;
    return 0;
}