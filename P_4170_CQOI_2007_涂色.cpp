#include <iostream>
#include <cstring>
using namespace std;

char s[55];
int dp[55][55];

int main() {
    cin >> s + 1;
    int n = strlen(s + 1);

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]);
            } 
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }
    cout << dp[1][n] << endl; 
    return 0;
}