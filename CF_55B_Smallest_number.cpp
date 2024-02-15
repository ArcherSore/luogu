#include <bits/stdc++.h>
using namespace std;
long long a[4];
char op[3];
long long ans = INT64_MAX;

long long order_cal() {
    long long ans = a[0];
    for (int i = 0; i < 3; i++) {
        if (op[i] == '+') {
            ans = ans + a[i + 1];
        } else {
            ans = ans * a[i + 1];
        }
    }
    return ans;
}

long long divid_cal() {
    long long ans, x, y;
    if (op[0] == '+') {
        x = a[0] + a[1];
    } else {
        x = a[0] * a[1];
    }
    if (op[1] == '+') {
        y = a[2] + a[3];
    } else {
        y = a[2] * a[3];
    }
    if (op[2] == '+') {
        ans = x + y;
    } else {
        ans = x * y;
    }
    return ans;
}

void dfs() {
    do {
        ans = min(ans, order_cal());
        ans = min(ans, divid_cal());
    } while (next_permutation(a, a + 4));
    cout << ans << endl;
    return;
}

int main() {
    for (int i = 0; i < 4; i++) cin >> a[i];
    sort(a, a + 4);
    for (int i = 0; i < 3; i++) cin >> op[i];
    dfs();
    return 0;
}