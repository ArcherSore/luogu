#include <bits/stdc++.h>
using namespace std;

int dp[1005][6005];

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        sum += a[i] + b[i];
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[1][a[1]] = 0, dp[1][b[1]] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 6 * n; j++) {
            if(j >= a[i]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - a[i]]);
            }
            if (j >= b[i]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - b[i]] + 1);
            }
        }
    }
    // for (int i = 0; i <= sum; i++) {
    //     cout << dp[n][i] << " ";
    // }
    // cout << endl;

    int delta = 6005, ans = n;
    for (int i = 0; i <= sum; i++) {
        if (dp[n][i] == 0x3f) {
            continue;
        }
        int x = abs(sum - 2 * i);
        if (x < delta) {
            delta = x;
            ans = dp[n][i];
        }
        if (x == delta) {
            ans = min(ans, dp[n][i]);
        }
    }
    cout << ans << endl;
    return 0;
}