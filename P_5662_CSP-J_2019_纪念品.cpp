#include <iostream>
#include <cstring>
using namespace std;

const int MAXT = 105;
const int MAXN = 105;
const int MAXM = 1e4 + 5;
int dp[MAXM] = {0}, p[MAXT][MAXN];

int main() {
    int t, n, m;
    cin >> t >> n >> m;
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> p[i][j];
        }
    }
    for (int i = 1; i < t; i++) {
        memset(dp, 0, sizeof(dp));
        for (int k = 1; k <= n; k++) {
            for (int j = p[i][k]; j <= m; j++) {
                dp[j] = max(dp[j], dp[j - p[i][k]] + p[i + 1][k] - p[i][k]);
            }
        }
        // 第二天全卖(i < t)
        m += dp[m];
    }
    
    cout << m << endl;
    return 0;
}