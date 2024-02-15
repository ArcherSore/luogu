#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

int vis[1025][1025];
string line[1005];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Point {
    int x, y;
};

void bfs(int x0, int y0, int n) {
    queue<Point> q;
    q.push({x0, y0});
    vis[x0][y0] = 1;
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i], y = p.y + dy[i];
            if (vis[x][y] || x < 0 || x >= n || y < 0 || y >= line[x].size() || line[x][y] == '*' || line[x][y] == ' ') continue;
            q.push({x, y});
            vis[x][y] = 1;
        }
    }
    return;
}

void output(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < line[i].size(); j++) {
            cout << vis[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    int n;
    cin >> n;
    getline(cin, line[100]);
    // cout << "n = " << n << endl;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        for (auto c : s) {
            if (c != '\r' && c != '\n') {
                line[i] += c;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < line[i].size(); j++) {
            if (!vis[i][j] && isalpha(line[i][j])) {
                bfs(i, j, n);
                // cout << i << " " << j << endl;
                ans++;
                // output(n);
            }
        }
    }
    cout << ans << endl;
    return 0;
}