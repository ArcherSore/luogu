#include <iostream>
using namespace std;

const int MAXN = 40;
int dp[MAXN] = {0};

int main() {
    int n;
    cin >> n;
    
    int Max = 0, ans = 0;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        for (int k = 0; k < 32; k++) {
            if ((1 << k) & a) {
                Max = max(dp[k] + 1, Max);
            }
        }
        for (int k = 0; k < 32; k++) {
            if ((1 << k) & a) {
                dp[k] = max(dp[k], Max);
            }
        }
        ans = max(ans, Max);
    }

    cout << ans << endl;
    return 0;
}