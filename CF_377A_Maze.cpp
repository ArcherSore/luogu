#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 505;
char a[MAXN][MAXN];
int num[MAXN][MAXN] = {0}; // '.'周围有几个'#'
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct Point {
    int x, y;
};

int main() {
    int n, m, k, cnt_X = 0, sx, sy;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '.') {
                cnt_X++;
                a[i][j] = 'X';
                sx = i, sy = j;
            }           
        }
    }

    queue<Point> q;
    q.push({sx, sy});
    while (!q.empty()) {
        if (cnt_X == k)
            break;
        Point p = q.front();
        q.pop();
        if (a[p.x][p.y] == '.')
            continue;
        a[p.x][p.y] = '.';
        cnt_X -= 1;
        for (int k = 0; k < 4; k++) {
            int x = p.x + dx[k], y = p.y + dy[k];
            if (x < 1 || x > n || y < 1 || y > m)
                continue;
            if (a[x][y] == 'X')
                q.push({x, y});                
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}