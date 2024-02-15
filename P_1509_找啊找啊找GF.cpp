#include <iostream>
using namespace std;

const int MAXN = 105;
int dp[MAXN][MAXN];
int dpt[MAXN][MAXN];
int r[MAXN], rp[MAXN], t[MAXN];

int main() {
    int n, M, R;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> rp[i] >> t[i];
    }
    cin >> M >> R;
    for (int i = 0; i < n; i++) {
        for (int j = M; j >= r[i]; j--) {
            for (int k = R; k >= rp[i]; k--) {
                if (dp[j][k] < dp[j - r[i]][k - rp[i]] + 1) {
                    dp[j][k] = dp[j - r[i]][k - rp[i]] + 1;
                    dpt[j][k] = dpt[j - r[i]][k - rp[i]] + t[i];
                } else if (dp[j][k] == dp[j - r[i]][k - rp[i]] + 1) {
                    dpt[j][k] = min(dpt[j][k], dpt[j - r[i]][k - rp[i]] + t[i]);
                }
            }
        }
    }
    cout << dpt[M][R] << endl;
    return 0;
}