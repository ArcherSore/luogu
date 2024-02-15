#include <iostream>
#include <cstring>
using namespace std;

int val[105][105] = {{0}};
int dp[105][105] = {{0}};
int pre[105][105]; // 记录dp[i][j]由谁转移过来的
int ans[105];

void print(int n, int tt) {
    if (n) {
        ans[n] = tt;
        print(n - 1, pre[n][tt]);
    }
    return;
}

int main() {
    int F, V;
    cin >> F >> V;
    for (int i = 1; i <= F; i++) {
        for (int j = 1; j <= V; j++) {
            cin >> val[i][j];
        }
    }

    // init
    for (int i = 1; i <= V - F; i++) {
        dp[1][i] = val[1][i];
        pre[1][i] = i;
    }
    // transform
    for (int i = 2; i <= F; i++) {
        for (int j = i; j <= V - F + i; j++) {
            for (int k = 1; k < j; k++) {
                if (dp[i - 1][k] + val[i][j] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][k] + val[i][j];
                    pre[i][j] = k;
                }
            }
        }
    }

    int res = 0, tt; // tt记录最后一朵花放在哪个花瓶
    for (int i = F; i <= V; i++) {
        if (dp[F][i] > res) {
            res = dp[F][i];
            tt = i;
        }
    }
    cout << res << endl;
    print(F, tt);
    for (int i = 1; i <= F; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}