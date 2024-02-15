#include <iostream>
using namespace std;

const int MAXN = 5005;
int dp[MAXN], val[MAXN];
int f[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int n, max_len = 0, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    val[0] = INT32_MAX;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (val[j] <= val[i]) continue;
            dp[i] = max(dp[i], dp[j] + 1);
        }
        for (int j = 0; j < i; j++) {
            if (val[j] < val[i]) continue;
            if (val[j] > val[i] && dp[j] + 1 == dp[i]) {
                f[i] += f[j];
            }
            if (val[j] == val[i] && dp[j] == dp[i]) {
                f[j] = 0;
            }
        }
        max_len = max(max_len, dp[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (dp[i] == max_len) 
            ans += f[i];
    }
    cout << max_len << " " << ans << endl;
    return 0;
}