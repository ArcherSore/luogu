#include <bits/stdc++.h>
using namespace std;

const int MAXT = 3e5 + 5;
int dp[MAXT];

int main() {
    int m, s, t;
    cin >> m >> s >> t;
    dp[0] = 0;
    // 能闪则闪
    for (int i = 1; i <= t; i++) {
        if (m >= 10) {
            m -= 10;
            dp[i] = dp[i - 1] + 60;
        } else {
            m += 4;
            dp[i] = dp[i - 1];
        }
    }
    // 走路能不能更优
    for (int i = 1; i <= t; i++) {
        if (dp[i] < dp[i - 1] + 17)
            dp[i] = dp[i - 1] + 17;
        if (dp[i] >= s) {
            cout << "Yes\n" << i << endl;
            return 0;
        }
    }
    cout << "No\n" << dp[t] << endl;
    return 0;
}