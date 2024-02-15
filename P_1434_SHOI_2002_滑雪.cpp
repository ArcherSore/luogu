#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 105;
int f[MAXN][MAXN] = {0};
int val[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

struct Point {
    int x, y;
    bool operator<(const Point &a) const {
        return val[x][y] > val[a.x][a.y];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    priority_queue<Point> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = 1;
            cin >> val[i][j];
            Point a;
            a.x = i, a.y = j;
            q.push(a);
        }
    }
    int ans = 0;
    while (!q.empty()) {
        Point a = q.top();
        int i = a.x, j = a.y;
        // printf("i = %d, j = %d, val = %d\n", i, j, val[i][j]);
        q.pop();
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (val[x][y] < val[i][j]) {
                f[i][j] = max(f[i][j], f[x][y] + 1);
            }
        }
        ans = max(ans, f[i][j]);
    }
    cout << ans << endl;
    return 0;
}