#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
int dp[MAXN] = {0}; // 能否达到高度i
int ans[MAXN] = {0};
int hei[105];

void output(int max_height, int n) {
    for (int i = max_height; i >= 0; i--) {
        if (ans[i] == n) {
            cout << i << endl;
            return;
        }
    }
    cout << 0 << endl;
    return;
}

int main() {
    int n, max_height = 0;
    cin >> n;
    for (int k = 0; k < n; k++) {
        memset(dp, 0, sizeof(dp));
        int len, cnt = 0, height = 0;
        while (cin >> len && len != -1) {
            hei[++cnt] = len;
            height += len;
        }
        max_height = max(max_height, height);

        dp[0] = 1;
        for (int i = 1; i <= cnt; i++) {
            for (int j = height; j >= hei[i]; j--) {
                if (dp[j] == 0)
                    dp[j] = dp[j - hei[i]];
            }
        }

        // for (int i = 0; i <= height; i++) {
        //     cout << dp[i] << " ";
        // }
        // cout << endl;

        for (int i = 1; i <= height; i++) {
            if (dp[i]) ans[i]++;
        }
    }

    output(max_height, n);
    return 0;
}