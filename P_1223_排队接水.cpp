#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
long long wait[MAXN] = {0};
struct Person {
    int t, id;
} arr[MAXN];

bool cmp(const Person &a, const Person &b) {
    return a.t < b.t;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].t;
        arr[i].id = i;
    }
    sort(arr + 1, arr + n + 1, cmp);
    double ans = 0.0;
    for (int i = 2; i <= n; i++) {
        wait[i] = wait[i - 1] + arr[i - 1].t;
        ans += wait[i];
    }
    // cout << ans << endl;
    ans = 1.0 * ans / n;
    for (int i = 1; i <= n; i++) {
        cout << arr[i].id << " ";
    }
    printf("\n%.2lf", ans);
    return 0;
}