#include <iostream>
using namespace std;

const int MAXN = 105;
int x[MAXN], dp[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + x[i];
        for (int j = 0; j < i - 1; j++) {
            dp[i] = max(dp[i], dp[j] + abs(x[j + 1] - x[i]) * (i - j));
        }
    }   
    cout << dp[n] << endl;
    return 0;
}