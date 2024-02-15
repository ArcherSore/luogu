#include <iostream>
using namespace std;

const int MAXN = 2505;
const int INF = 0x3f;
int a[MAXN], sum[MAXN] = {0};
int dp[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 2) 
            a[i] = -1;
        sum[i] = sum[i - 1] + a[i];
        dp[i] = INF;
    }
    dp[0] = 0, dp[1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (abs(sum[i] - sum[j - 1]) <= m || abs(sum[i] - sum[j - 1]) == i - j + 1) {
                dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }
        // cout << dp[i] << " ";
    }
    cout << dp[n] << endl;
    return 0;
}