#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e4 + 5;
int a[MAXN];

int main() {
    int w, n;
    cin >> w >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int i = 0, j = n - 1, ans = 0;
    while (i < j) {
        if (a[i] + a[j] <= w) {
            ans += 1;
            i += 1;
            j -= 1;
        } else {
            ans += 1;
            j -= 1;
        }
    }
    if (i == j)
        ans += 1;
    cout << ans << endl;
    return 0;
}