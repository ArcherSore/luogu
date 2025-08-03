#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

void work() {
    freopen("out.txt", "w", stdout);
    const int N = 30;
    vector<vector<int>> sg(N, vector<int> (N, -1));
    vector<int> vis(N * N + 1);
    sg[1][1] = 0;
    for (int s = 3; s <= 2 * (N - 1); s++) {
        for (int i = 1; i <= s - i; i++) {
            int j = s - i;
            if (i >= N || j >= N) {
                continue;;
            }
            fill(vis.begin(), vis.end(), 0);
            // break down i
            for (int a = 1; a <= i - a; a++) {
                int b = i - a;
                if (a >= N || b >= N) {
                    continue;
                }
                vis[sg[a][b]] = 1;
            }
            // break down j
            for (int a = 1; a <= j - a; a++) {
                int b = j - a;
                if (a >= N || b >= N) {
                    continue;
                }
                vis[sg[a][b]] = 1;
            }

            for (int x = 0; x < N * N; x++) {
                if (!vis[x]) {
                    sg[i][j] = x;
                    break;
                }
            }
        }
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            cout << ' ' << ' ';
        }
        for (int j = i; j < N; j++) {
            cout << sg[i][j] << ' ';
        }
        cout << endl;
    }
    cout << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<int> sg(n / 2);
    for (int i = 0, x, y; i < n / 2; i++) {
        cin >> x >> y;
        int t = (x - 1) | (y - 1);
        while (t & 1) {
            t >>= 1;
            sg[i]++;
        }
    }
    int res = 0;
    for (int x : sg) {
        res ^= x;
    }
    if (res) {
        cout << "YES\n"; 
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;

    // work();

    while (T--) {
        solve();
    }

    return 0;
}