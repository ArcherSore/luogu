#include <bits/stdc++.h>
using namespace std;

const int MAXV = 5005;
const int MAXK = 55;
int dp[MAXV][MAXK];
int tmp[MAXK]; 

int main() {
    int K, V, N;
    cin >> K >> V >> N;

    // dp[i][0]存最优值的数量
    dp[0][0] = 1, dp[0][1] = 0;
    for (int i = 0, v, w; i < N; i++) {
        cin >> v >> w;
        for (int j = V; j >= v; j--) {
            int p1 = 1, p2 = 1, t = 1;
            int n1 = dp[j][0], n2 = dp[j - v][0];
            // 归并排序
            while (p1 <= n1 || p2 <= n2) {
                if (p2 > n2 || (p1 <= n1 && dp[j][p1] >= dp[j - v][p2] + w)) {
                    tmp[t++] = dp[j][p1++];
                } else {
                    tmp[t++] = dp[j - v][p2++] + w;
                }
                if (t > K) {
                    break;
                }
            }
            tmp[0] = t - 1;
            memcpy(dp[j], tmp, sizeof(int) * t);
        }
    }
    int ans = 0;
    for (int i = 1; i <= K; i++) {
        ans += dp[V][i];
    }
    cout << ans << endl;
    return 0;
}