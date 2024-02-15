#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN];

int main() {
    int n, x;
    cin >> n >> x;

    long long ans = 0;   
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i) {
            if (a[i - 1] + a[i] > x) {
                ans += (a[i - 1] + a[i] - x);
                a[i] = x - a[i - 1];
            }
        } else {
            if (a[i] > x) {
                ans += (a[i] - x);
                a[i] = x;
            }
        }
    }
    cout << ans << endl;
    return 0;
}