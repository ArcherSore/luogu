#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<LL, LL>;

void floyd(vector<vector<int>> &a, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] |= a[i][k] & a[k][j];
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector a(n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    floyd(a, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }

    return ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}