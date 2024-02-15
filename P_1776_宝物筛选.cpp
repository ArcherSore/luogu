#include <bits/stdc++.h>
using namespace std;

const int MAXW = 4e4 + 5;
long long dp[MAXW] = {0};

int main() {
    int n, W;
    cin >> n >> W;

    for (int i = 1, v, w, m; i <= n; i++) {
        cin >> v >> w >> m;
        for (int k = 1; m; m -= k, k *= 2) {
            k = min(m, k);
            for (int j = W; j >= k * w; j--) {
                dp[j] = max(dp[j], dp[j - k * w] + k * v);
            }   
        }
    }
    long long ans = 0;
    for (int i = 1; i <= W; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}