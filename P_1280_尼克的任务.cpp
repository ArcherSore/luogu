#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e4 + 5;

vector<vector<int> > v(MAXN);
int dp[MAXN];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1, p, t; i <= k; i++) {
        cin >> p >> t;
        v[p].push_back(t);
    }

    for (int i = n; i >= 1; i--) {
        if (v[i].size() == 0) {
            dp[i] = dp[i + 1] + 1;
        } else {
            for (auto t : v[i]) {
                dp[i] = max(dp[i], dp[i + t]);
            }
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << dp[i] << " ";
    // }
    
    cout << dp[1] << endl;
    return 0;
}