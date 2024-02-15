#include <bits/stdc++.h>
using namespace std;

const int MAXN = 45;
int dp[MAXN][MAXN][MAXN];
int val[400];
int cnt[4];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 0, a; i < m; i++) {
        cin >> a;
        cnt[a - 1] += 1;
    }

    for (int a = 0; a <= cnt[0]; a++) {
        for (int b = 0; b <= cnt[1]; b++) {
            for (int c = 0; c <= cnt[2]; c++) {
                for (int d = 0; d <= cnt[3]; d++) {
                    int s = a + 2 * b + 3 * c + 4 * d;
                    int ans = dp[b][c][d];
                    if (b > 0) ans = max(ans, dp[b - 1][c][d]);
                    if (c > 0) ans = max(ans, dp[b][c - 1][d]);
                    if (d > 0) ans = max(ans, dp[b][c][d - 1]);
                    dp[b][c][d] = ans + val[s];
                }
            }
        }
    }
    cout << dp[cnt[1]][cnt[2]][cnt[3]] << endl;
    return 0;
}