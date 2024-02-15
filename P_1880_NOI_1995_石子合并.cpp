#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
int a[MAXN], sum[MAXN];
int dp[MAXN][MAXN];


int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    
    // min
    int ans = INT32_MAX;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= 2 * n; i++) {
        dp[i][i] = 0;
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= 2 * n - l + 1; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
        
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[i][i + n - 1]);
    }
    cout << ans << endl;

    // max
    ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= 2 * n - l + 1; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
        
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i][i + n - 1]);
    }
    cout << ans << endl;
    return 0;
}