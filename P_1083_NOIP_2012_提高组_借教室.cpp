#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int a[MAXN] = {0}, d[MAXN] = {0}, pre[MAXN] = {0};
struct Rent {
    int day, s, t;
} rent[MAXN];

bool check(int mid, int n) {
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= mid; i++) {
        d[rent[i].s] += rent[i].day;
        d[rent[i].t + 1] -= rent[i].day;
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + d[i];
        if (pre[i] > a[i])
            return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> rent[i].day >> rent[i].s >> rent[i].t;
    }
    if (check(m, n)) {
        cout << 0 << endl;
        return 0;
    }
    int left = 1, right = n, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (!check(mid, n)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    if (m != right)
        printf("%d\n%d\n", -1, right);
    else 
        cout << 0 << endl;
    return 0;
}