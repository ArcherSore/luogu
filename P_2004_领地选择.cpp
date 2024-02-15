#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 5;
int a[MAXN][MAXN] = {{0}}, pre[MAXN][MAXN] = {{0}};

int main() {
    int n, m, c;
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + a[i][j];
        }
    }
    int ans = INT32_MIN, sum, x, y;
    for (int i = c; i <= n; i++) {
        for (int j = c; j <= n; j++) {
            sum = pre[i][j] - pre[i - c][j] - pre[i][j - c] + pre[i - c][j - c];
            if (sum > ans) {
                ans = sum;
                x = i - c + 1, y = j - c + 1;
            }
        }
    }
    cout << x << " " << y << endl;
    return 0;
}