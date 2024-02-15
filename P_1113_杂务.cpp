#include <iostream>
using namespace std;

const int MAXN = 1e4 + 5;
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int n, ans = 0;
    cin >> n;
    for (int i = 1, t, j; i <= n; i++) {
        cin >> i >> t;
        dp[i] = t;
        while (cin >> j && j) {
            dp[i] = max(dp[i], dp[j] + t);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}