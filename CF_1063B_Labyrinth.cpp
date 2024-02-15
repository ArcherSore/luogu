#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int INF = 4e6;
char a[MAXN][MAXN];
int l_step[MAXN][MAXN], r_step[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dl[4] = {0, 0, 1, 0};
int dr[4] = {0, 0, 0, 1};
struct Point {
    int x, y, lstep, rstep;
};

int main() {
    int n, m, x0, y0, max_l, max_r;
    cin >> n >> m >> x0 >> y0 >> max_l >> max_r;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            l_step[i][j] = INF, r_step[i][j] = INF;
        }
    }
    queue<Point> q;
    l_step[x0][y0] = r_step[x0][y0] = 0;
    a[x0][y0] = '+';
    q.push({x0, y0, 0, 0});
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i], y = p.y + dy[i], l = p.lstep + dl[i], r = p.rstep + dr[i];
            if (x < 1 || x > n || y < 1 || y > m || l > max_l || r > max_r || a[x][y] == '*')
                continue;
            if (a[x][y] == '.') {
                a[x][y] = '+';
                q.push({x, y, l, r});
                l_step[x][y] = l, r_step[x][y] = r;
            } else {
                // 已经来过
                if (l_step[x][y] <= l || r_step[x][y] <= r)
                    continue;
                q.push({x, y, l, r});
                l_step[x][y] = l, r_step[x][y] = r;
            }
        }
        // printf("x = %d, y = %d, l = %d, r = %d\n", p.x, p.y, p.lstep, p.rstep);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '+')
                cnt += 1;
        }
    }
    cout << cnt << endl;
    return 0;
}