#include <bits/stdc++.h>
using namespace std;

const int MAXN = 125;

int a[MAXN][MAXN] = {0}, sum[MAXN][MAXN] = {0};

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    }
    int ans = INT32_MIN;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int x = i; x <= n; x++) {
                for (int y = j; y <= n; y++) {
                    int area = sum[x][y] - sum[x][j - 1] - sum[i - 1][y] + sum[i - 1][j - 1];
                    ans = max(ans, area);
                    // printf("i = %d, j = %d, x = %d, y = %d, area = %d\n", i, j, x, y, area);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}