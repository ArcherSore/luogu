#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

long long a[100], dp[100][100];
long long m2[70];

void pre() {
    long long x = 1;
    for (int i = 0; i < 63; i++) {
        m2[i] = x;
        x *= 2;
    }
    return;
}

int main() {
    pre();
    int n, m;
    cin >> n >> m;
    long long ans = 0;
    while (n--) {
        for (int i = 1; i <= m; i++) {
            cin >> a[i];
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= m; i++) {
            for (int j = m; j >= i; j--) {
                int t = m - j + i - 1;
                dp[i][j] = max(dp[i][j], max(dp[i - 1][j] + a[i - 1] * m2[t], dp[i][j + 1] + a[j + 1] * m2[t]));
            }
        }
        long long MAX = 0;
        for (int i = 1; i <= m; i++) {
            MAX = max(MAX, dp[i][i] + a[i] * m2[m]);
        }
        // cout << MAX << endl;
        ans += MAX;
    }
    cout << ans << endl;
    return 0;
}