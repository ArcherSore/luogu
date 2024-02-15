#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

struct Money {
    int m, v;
    double q;
} arr[MAXN];

bool cmp(const Money &a, const Money &b) {
    return a.q < b.q;
}

int main() {
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].m >> arr[i].v;
        arr[i].q = 1.0 * arr[i].m / arr[i].v;
    }
    sort(arr, arr + n, cmp);
    double ans = 0;
    for (int i = 0; i < n; i++) {
       // cout << "t = " << t << ", m = " << arr[i].m << ", v = " << ans << endl;
        if (t >= arr[i].m) {
            ans += arr[i].v;
            t -= arr[i].m;
        } else {
            ans += t / arr[i].q;
            break;
        }
    }
    printf("%.2lf\n", ans);
    return 0;
}