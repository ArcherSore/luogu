#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1005;
const int MAXM = 100005;

struct Point {
    int x, y;
};

int map[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int vis[MAXN][MAXN];
int ans[MAXN * MAXN];

int bfs(int x0, int y0, int n, int cnt) {
    queue<Point> q;
    q.push({x0, y0});
    vis[x0][y0] = cnt;
    int num = 0;
    while (!q.empty()) {
        num++;
        Point p = q.front();
        // cout << p.x << " " << p.y << endl;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i], y = p.y + dy[i];
            if (!vis[x][y] && x >= 1 && x <= n && y >= 1 && y <= n && map[p.x][p.y] != map[x][y]) {
                q.push({x, y});
                vis[x][y] = cnt;
            }
        }
    }
    return num;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            map[i][j] = c - '0';
        }
    }
    queue<Point> q;
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!vis[i][j]) {
                ans[cnt] = bfs(i, j, n, cnt);
                cnt++;
            }
        }
    }

    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << ans[vis[x][y]] << endl;
    }
    return 0;
}