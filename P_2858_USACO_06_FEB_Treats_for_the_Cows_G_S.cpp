#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int v[MAXN], dp[MAXN][MAXN];
int pre[MAXN] = {0};

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        dp[i][i] = v[i];
        pre[i] = pre[i - 1] + v[i];
    }

    for (int i = n; i > 0; i--) {
        for (int j = i; j <= n; j++) {
            if (i == j) 
                continue;
            dp[i][j] = max(dp[i + 1][j] + pre[j] - pre[i - 1], dp[i][j - 1] + pre[j] - pre[i - 1]);
        }
    }
    
    cout << dp[1][n] << endl;
    return 0;
}