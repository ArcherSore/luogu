#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
char a[MAXN][MAXN];
int colored[MAXN][MAXN] = {0};
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool check(int i, int j) {
    for (int k = 0; k < 8; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (a[x][y] == '.') {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, cnt = 0, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '#')
                cnt += 1;
        }
    }
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 2; j <= m - 1; j++) {
            if (check(i, j)) {
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (!colored[x][y]) {
                        colored[x][y] = 1;
                        ans += 1;
                    }      
                }
            }
        }
    }
    if (cnt == ans)
        cout << "YES" << endl;
    else   
        cout << "NO" << endl;
    return 0;
}