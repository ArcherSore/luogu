#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 55;

int dp[MAXN][MAXN][2];
int sum[MAXN];

struct Light {
    int pos, power;
} light[MAXN];

int main() {
    int n, c;
    cin >> n >> c;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        cin >> light[i].pos >> light[i].power;
        sum[i] = sum[i - 1] + light[i].power;
    }

    dp[c][c][0] = dp[c][c][1] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j][0] = min(dp[i + 1][j][0] + (light[i + 1].pos - light[i].pos) * (sum[i] + sum[n] - sum[j]), 
                        dp[i + 1][j][1] + (light[j].pos - light[i].pos) * (sum[i] + sum[n] - sum[j]));
            dp[i][j][1] = min(dp[i][j - 1][0] + (light[j].pos - light[i].pos) * (sum[i - 1] + sum[n] - sum[j - 1]), 
                        dp[i][j - 1][1] + (light[j].pos - light[j - 1].pos) * (sum[i - 1] + sum[n] - sum[j - 1]));
        }
    }
    cout << min(dp[1][n][1], dp[1][n][0]) << endl;
    return 0;
}