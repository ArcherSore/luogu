#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2005;
int dp[MAXN][MAXN] = {{0}};
char a[MAXN], b[MAXN];

int main() {
    cin >> a + 1 >> b + 1;
    int n = strlen(a + 1), m = strlen(b + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // init
            dp[i][0] = i, dp[0][j] = j;
            if (a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}