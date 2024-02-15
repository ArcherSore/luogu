#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 305;

int dp[MAXN][MAXN];
int sum[MAXN];

int main() {
    int n;
    cin >> n;
    vector<int> m(n + 1);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
        sum[i] = sum[i - 1] + m[i];
        dp[i][i] = 0;
    }

    
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}