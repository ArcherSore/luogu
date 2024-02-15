#include <iostream>
#include <cstring>
using namespace std;

int a[105];
int dp1[105][105][15], dp2[105][105][15];
int sum[105];

int mod(int x) {
    return ((x % 10) + 10) % 10;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    // init
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, 0x3f, sizeof(dp2));
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = i; j <= 2 * n; j++) {
            dp1[i][j][1] = mod(sum[j] - sum[i - 1]);
            dp2[i][j][1] = dp1[i][j][1];
        }
    }
    // dp
    for (int k = 2; k <= m; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = i + k - 1; j <= i + n - 1; j++) {
                for (int p = i + k - 2; p < j; p++) {
                    dp1[i][j][k] = max(dp1[i][j][k], dp1[i][p][k - 1] * mod(sum[j] - sum[p]));
                    dp2[i][j][k] = min(dp2[i][j][k], dp2[i][p][k - 1] * mod(sum[j] - sum[p]));
                }
            }
        }
    }

    int MAX = -1, MIN = 0x7fffffff;
    for (int i = 1; i <= n; i++) {
        MAX = max(MAX, dp1[i][i + n - 1][m]);
        MIN = min(MIN, dp2[i][i + n - 1][m]);
    }
    cout << MIN << "\n" << MAX << "\n";
    return 0;
}