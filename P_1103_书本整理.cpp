#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 105;
int dp[MAXN][MAXN];
struct Data {
    int x, y;
} arr[MAXN];

int main() {
    int n, K;
    cin >> n >> K;
    K = n - K;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].x >> arr[i].y;
    }
    sort(arr + 1, arr + n + 1, [](const Data &a, const Data &b) {
        return a.x < b.x;
    });
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i][1] = 0;
        for (int k = 2; k <= i; k++) {
            for (int j = 1; j < i; j++) {
                dp[i][k] = min(dp[i][k], dp[j][k - 1] + abs(arr[j].y - arr[i].y));
            }
        }
    }
    int ans = 0x7fffffff;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[i][K]);
    }
    cout << ans << endl;
    return 0;
}