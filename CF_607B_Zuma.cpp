#include <iostream>
#include <cstring>
using namespace std;

int c[505], dp[505][505];

int main() {
    int n;
    cin >> n;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            if (c[i] == c[j]) {
                if (j == i + 1) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
                }
            }
            // else {
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            // }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}