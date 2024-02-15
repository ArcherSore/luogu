#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1005;
const int INF = 2e5;
int a[MAXN][MAXN] = {0}; // 0:无 1:红 2:黄
int cost[MAXN][MAXN] = {0};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct Point {
    int x, y, color, cost;
};

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        cin >> a[x][y];
        a[x][y] += 1;
    }

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            cost[i][j] = INF;
        }
    }
    cost[1][1] = 0;

    queue<Point> q;
    q.push({1, 1, a[1][1], 0});
    while (!q.empty()) {
        Point p = q.front();
        // cout << "x = " << p.x << ", y = " << p.y << ", cost = " << cost[p.x][p.y] << endl;
        if (p.x == n && p.y == n)
            break;
        q.pop();
        // 重复压入的次优解
        if (p.cost > cost[p.x][p.y])
            continue;
        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i], y = p.y + dy[i];
            if (x < 1 || x > n || y < 1 || y > n)
                continue;
            if (a[x][y] == 0) {
                if (a[p.x][p.y] == 0 || cost[x][y] <= p.cost + 2) 
                    continue;
                cost[x][y] = p.cost + 2;
                q.push({x, y, p.color, cost[x][y]});
            } else if (a[x][y] == p.color) {
                if (cost[x][y] <= p.cost) 
                    continue;
                cost[x][y] = p.cost;
                q.push({x, y, a[x][y], cost[x][y]});
            } else {
                if (cost[x][y] <= p.cost + 1) 
                    continue;
                cost[x][y] = p.cost + 1;
                q.push({x, y, a[x][y], cost[x][y]});
            }
        }
    }

    if (cost[n][n] == INF) 
        cout << "-1" << endl;
    else 
        cout << cost[n][n] << endl;
    return 0;
}