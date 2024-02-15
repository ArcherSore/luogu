#include <bits/stdc++.h>
using namespace std;

long long dp[805] = {0}; 

void solve() {
    int n;
    cin >> n;
    int sum = (1 + n) * n / 2;
    if (sum % 2 == 1) {
        cout << 0 << endl;
        return;
    }

    sum /= 2;

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = sum; j >= i; j--) {
            dp[j] += dp[j - i];
        }
    }
    cout << dp[sum] / 2 << endl;
    return;
}

int main() {
    solve();
    return 0;
}