#include <bits/stdc++.h>
using namespace std;

int a[105][105];
int dp[105][105][105] = {{{0}}};

void output(int n, int m, int k) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int t = 0; t < k; t++) {
                if (dp[i][j][t])
                    printf("dp[%d][%d][%d] = %d\n", i, j, t, dp[i][j][t]);
            }
        }
    }
}

int main() {
    int M, N, K;
    cin >> M >> N >> K;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> a[i][j];
            a[i][j] %= K;
        }
    }
    dp[1][1][a[1][1]] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 0; k < K; k++) {
                if (dp[i][j][k]) {
                    if (i + 1 <= M) {
                        dp[i + 1][j][k * a[i + 1][j] % K] = dp[i][j][k];
                    }
                    if (j + 1 <= N) {
                        dp[i][j + 1][k * a[i][j + 1] % K] = dp[i][j][k];
                    }
                }
                    
            }
        }
    }
    // output(M, N, K);
    int cnt = 0;
    for (int i = 0; i < K; i++) {
        if (dp[M][N][i])
            cnt++;
    }
    cout << cnt << endl;
    for (int i = 0; i < K; i++) {
        if (dp[M][N][i])
            cout << i << " ";
    }
    return 0;
}