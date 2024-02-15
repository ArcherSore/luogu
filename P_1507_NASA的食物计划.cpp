#include <iostream>
using namespace std;

const int MAXH = 400;
const int MAXT = 400;
int dp[MAXH][MAXT];

int main() {
    int H, T, n;
    cin >> H >> T >> n;
    for (int i = 0, h, t, k; i < n; i++) {
        cin >> h >> t >> k;
        for (int j1 = H; j1 >= h; j1--) {
            for (int j2 = T; j2 >= t; j2--) {
                dp[j1][j2] = max(dp[j1][j2], dp[j1 - h][j2 - t] + k);
            }
        }
    }
    cout << dp[H][T] << endl;
    return 0;
}