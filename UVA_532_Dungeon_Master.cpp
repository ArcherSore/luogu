#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, z;
    int step;
};

char m[105][105][105];
int vis[105][105][105]; // 漏打了个0！！！！！！！！！草
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    int L, R, C;
    while (cin >> L >> R >> C) {
        memset(vis, 0, sizeof(vis));
        int sx, sy, sz, ex, ey, ez; // 起点坐标 终点坐标
        if (L == 0 && R == 0 && C == 0) break;
        for (int i = 1; i <= L; i++) {
            for (int j = 1; j <= R; j++) {
                for (int k = 1; k <= C; k++) {
                    cin >> m[i][j][k];
                    if (m[i][j][k] == 'S')
                        sx = i, sy = j, sz = k;
                    if (m[i][j][k] == 'E') 
                        ex = i, ey = j, ez = k;
                }
            }
        }
        
        int get = 0, ans; // get判断能否到达
        queue<Point> q;
        vis[sx][sy][sz] = 1;
        q.push({sx, sy, sz, 0});
        while (!q.empty()) {
            Point p = q.front();
            q.pop();
            if (p.x == ex && p.y == ey && p.z == ez) {
                // 到达终点
                get = 1; 
                ans = p.step;
                break;
            }
                
            for (int i = 0; i < 6; i++) {
                int x = p.x + dx[i], y = p.y + dy[i], z = p.z + dz[i];
                if (x < 1 || x > L || y < 1 || y > R || z < 1 || z > C || vis[x][y][z] || m[x][y][z] == '#') {
                    // 越界or重复走or为障碍
                    continue;
                }
                vis[x][y][z] = 1;
                q.push({x, y, z, p.step + 1});
            }
        }
        if (get) cout << "Escaped in " << ans << " minute(s).\n";
        else cout << "Trapped!\n";
    }
    return 0;
}