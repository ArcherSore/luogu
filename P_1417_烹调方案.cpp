#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1e5 + 5;

long long dp[MAXT] = {0};
struct Food {
    long long a, b, c;
} food[55];

bool cmp(const Food &x, const Food &y) {
    return x.c * y.b < x.b * y.c;
}

int main() {
    int T, n;
    cin >> T >> n;
    for (int i = 1; i <= n; i++)
        cin >> food[i].a;
    for (int i = 1; i <= n; i++)
        cin >> food[i].b;
    for (int i = 1; i <= n; i++)
        cin >> food[i].c;
    sort(food + 1, food + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        for (int j = T; j >= food[i].c; j--) {
            dp[j] = max(dp[j], dp[j - food[i].c] + food[i].a - j * food[i].b);
        }
    }
    long long ans = 0;
    for (int i = 0; i <= T; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}