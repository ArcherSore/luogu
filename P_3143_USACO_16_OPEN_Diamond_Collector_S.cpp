#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector<int> l(n + 1), r(n + 1);
    int p = 0;
    for (int i = 0; i < n; i++) {
        while (a[i] - a[p] > k) {
            p++;
        }
        l[i] = max(l[i - 1], i - p + 1);
    }
    p = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[p] - a[i] > k) {
            p--;
        }
        r[i] = max(r[i + 1], p - i + 1);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, l[i] + r[i]);
    }
    cout << ans << endl;
    return 0;
}