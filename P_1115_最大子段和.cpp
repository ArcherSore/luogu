#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int f, ans = INT32_MIN;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        if (i) {
            f = max(a, a + f);
            ans = max(ans, f);
        } else {
            f = a;
        }
    }
    cout << ans << endl;
    return 0;
}