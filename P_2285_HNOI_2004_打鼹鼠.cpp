#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1e4 + 5;
int t[MAXM], x[MAXM], y[MAXM], f[MAXM];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> t[i] >> x[i] >> y[i];
        f[i] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < i; j++) {
            if (abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j])
                f[i] = max(f[i], f[j] + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
    return 0;
}