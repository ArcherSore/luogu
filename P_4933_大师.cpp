#include <iostream>
using namespace std;

const int MOD = 998244353;
const int MAXV = 20000;
const int MAXN = 1000;

int h[MAXN + 5];
int dp[MAXN + 5][2 * MAXV + 10];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    // // init
    // for (int i = 1; i <= n; i++) {
    //     dp[i][MAXV] = i;
    // }

    // dp
    int ans = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][h[i] - h[j] + MAXV] += dp[j][h[i] - h[j] + MAXV] + 1;
            dp[i][h[i] - h[j] + MAXV] %= MOD;
            ans += dp[j][h[i] - h[j] + MAXV] + 1;
            ans %= MOD;
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j <= 40; j++) {
    //         cout << dp[i][j + MAXV] << " ";
    //     }
    //     cout << endl;
    // }
    cout << ans << endl;
    return 0;
}