#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
long long dp[MAXN];

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    dp[0] = 1, dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (!is_prime(i))
            continue;
        for (int j = 0; j <= n; j++) {
            if (j + i > n) {
                continue;
            }
            dp[j + i] += dp[j];
        }
    }
    cout << dp[n] << endl;
    return 0;
}