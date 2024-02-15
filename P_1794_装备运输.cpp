#include <bits/stdc++.h>
using namespace std;

int dp[505][505];

int main() {
    int V, G, n;
    cin >> V >> G >> n;
    for (int i = 1, t, v, g; i <= n; i++) {
        cin >> t >> v >> g;
        for (int j = V; j >= v; j--) {
            for (int k = G; k >= g; k--) {
                dp[j][k] = max(dp[j][k], dp[j - v][k - g] + t);
            }
        }
    }
    cout << dp[V][G] << endl;
    return 0;
}