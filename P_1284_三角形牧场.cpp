#include <bits/stdc++.h>
using namespace std;

int dp[805][805] = {0};

bool is_tri(int a, int b, int C) {
    int c = C - a - b;
    if (a < b) swap(a, b);
    if (a < c) swap(a, c);
    if (b < c) swap(b, c);
    if (c + a > b && c - a < b) {
        return true;
    }
    return false;
}

double area(int a, int b, int C) {
    int c = C - a - b;
    double p = C / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    int n, C = 0;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        C += a[i];
    }
    
    dp[0][0] = 1;
    for (int k = 1; k <= n; k++) {
        for (int i = C / 2; i >= 0; i--) {
            for (int j = C / 2; j >= 0; j--) {
                if (i >= a[k] && dp[i - a[k]][j]) dp[i][j] = 1;
                if (j >= a[k] && dp[i][j - a[k]]) dp[i][j] = 1;
            }
        }
    }

    double ans = 0.0;
    for (int i = C / 2; i > 0; i--) {
        for (int j = C / 2; j > 0; j--) {
            if (dp[i][j] && is_tri(i, j, C)) {
                ans = max(ans, area(i, j, C));
            }
        }
    }
    if (ans == 0.0) {
        cout << "-1" << endl;
    } else {
        cout << int(ans * 100) << endl;
    }
    return 0;
}