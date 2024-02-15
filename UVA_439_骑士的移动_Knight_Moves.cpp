#include <bits/stdc++.h>
using namespace std;

int vis[10][10] = {0};
int dx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
struct Point {
    int x, y, step;
};

int main() {
    string str, end;
    while (cin >> str >> end) {
        int x0, y0, x1, y1;
        x0 = str[0] - 'a' + 1;
        y0 = str[1] - '0';
        x1 = end[0] - 'a' + 1;
        y1 = end[1] - '0';
        queue<Point> q;
        memset(vis, 0, sizeof(vis));
        q.push({x0, y0, 0});
        vis[x0][y0] = 1;
        while (!q.empty()) {
            Point p = q.front();
            q.pop();
            for (int i = 0; i < 8; i++) {
                int x = p.x + dx[i], y = p.y + dy[i];
                if (x < 1 || x > 8 || y < 1 || y > 8 || vis[x][y])
                    continue;
                q.push({x, y, p.step + 1});
                vis[x][y] = 1;
            }
            if (p.x == x1 && p.y == y1)
                cout << "To get from " << str << " to " << end << " takes " << p.step << " knight moves.\n";
        }
    }
    return 0;
}