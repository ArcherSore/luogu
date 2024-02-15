#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1e5;
int dp[MAXS], a[15], b[15];

int main() {
    int s, n, d, sum;
    cin >> s >> n >> d;
    sum = s;
    for (int i = 1; i <= d; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        memset(dp, 0, sizeof(dp));
        for (int j = 1; j <= d; j++) {
            for (int k = a[j] / 1000; k <= sum / 1000; k++) {
                dp[k] = max(dp[k], dp[k - a[j] / 1000] + b[j]);
            }
        }
        sum += dp[sum / 1000];
    }
    cout << sum << endl;
    return 0;
}