#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1005;
int h1, m1, h2, m2, n;
int dp[MAXT];

void input() {
    cin >> h1;
    getchar();
    cin >> m1 >> h2;
    getchar();
    cin >> m2 >> n;
    return;
}

int main() {
    input();
    int T = (h2 - h1) * 60 + (m2 - m1);
    for (int i = 1, t, c, p; i <= n; i++) {
        cin >> t >> c >> p;
        int ind = i % 2, rind = (i - 1) % 2;
        if (p) {
            // 多重背包
            for (int k = 1; p; p -= k, k *= 2) {
                k = min(k, p);
                for (int j = T; j >= k * t; j--) {
                    dp[j] = max(dp[j], dp[j - k * t] + k * c);
                }
            }
        } else {
            // 完全背包
            for (int j = t; j <= T; j++) {
                dp[j] = max(dp[j], dp[j - t] + c);
            }
        }
    }
    cout << dp[T] << endl;
    return 0;
}