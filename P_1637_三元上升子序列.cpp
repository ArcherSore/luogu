#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
int n, a[MAXN];
long long f[MAXN][4];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][1] = 1;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] >= a[i])
                continue;
            f[i][2] += f[j][1];
            f[i][3] += f[j][2];
        }
        ans += f[i][3];
    }
    cout << ans << endl;
    return 0;
}