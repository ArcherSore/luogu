#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int MAXT = 1e4 + 5;
int v[MAXN], c[MAXN];
int dp[2 * MAXT];

void output(int n) {
    for (int i = 1; i <= n; i++) {
        cout << "dp[" << i << "] = " << dp[i] << endl;
    }
    return;
}

int main() {
    int N, T;
    cin >> N >> T;
    int max_v = 0;
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
        max_v = max(max_v, v[i]);
    }
    for (int i = 1; i <= N; i++) {
        cin >> c[i];
    }
    // init
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    // 多重
    for (int i = 1; i <= N; i++) {
        int s = c[i];
        for (int k = 1; s; s -= k, k *= 2) {
            k = min(k, s);
            for (int j = T + max_v; j >= k * v[i]; j--) {
                dp[j] = min(dp[j], dp[j - k * v[i]] + k);
            }
        }
        // 
        // output(T + max_v);
    }
    // 
    // output(T + max_v);
    // 完全
    for (int i = 1; i <= N; i++) {
        for (int j = T; j <= T + max_v; j++) {
            dp[j] = min(dp[j], dp[j + v[i]] + 1);
        }
    }
    // 
    // output(T + max_v);
    if (dp[T] != 1061109567) cout << dp[T] << endl;
    else cout << -1 << endl;
    return 0;
}