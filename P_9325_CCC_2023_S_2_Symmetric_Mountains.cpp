#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
int a[MAXN], dp[MAXN][MAXN], ans[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    memset(ans, 0x3f, sizeof(ans));
    // odd
    for (int i = 0; i < MAXN; i++) {
        dp[i][i] = 0;
    }
    for (int len = 3; len <= n; len += 2) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + abs(a[i] - a[j]));
            ans[len] = min(ans[len], dp[i][j]);
        }
    }
    // even
    for (int i = 1; i < MAXN; i++) {
        dp[i][i - 1] = abs(a[i] - a[i - 1]);
        dp[i - 1][i] = abs(a[i] - a[i - 1]);
    }
    for (int len = 2; len <= n; len += 2) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + abs(a[i] - a[j]));
            ans[len] = min(ans[len], dp[i][j]);
        }
    }

    ans[1] = 0;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}