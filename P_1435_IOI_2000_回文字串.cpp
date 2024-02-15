#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
char s[MAXN], t[MAXN];
int dp[MAXN][MAXN] = {{0}};

int main() {
    cin >> s + 1;
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        t[i] = s[n - i + 1];
    }

    int max_len = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
            if (dp[i][j] > max_len) {
                max_len = dp[i][j];
            }
        }
    }
    cout << n - max_len << endl;
    return 0;    
}