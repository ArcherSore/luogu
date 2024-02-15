#include <iostream>
using namespace std;

char map[55][55];
string dir[1005];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool vis[1005][55][55];
int n, m, st_x, st_y, cnt;


int get_pos(int x) {
    if (dir[x][0] == 'N') return 0;
    if (dir[x][0] == 'S') return 1;
    if (dir[x][0] == 'W') return 2;
    if (dir[x][0] == 'E') return 3;
    return -1;
}

void dfs(int opt, int x, int y) {
    if (vis[opt][x][y]) return; //已经搜索过了
    vis[opt][x][y] = 1;
    
    if (opt == cnt) {
        map[x][y] = '*';
        return;
    }

    int p = get_pos(opt);
    while (0 <= x + dx[p] && x + dx[p] < n && 0 <= y + dy[p] && y + dy[p] < m && map[x + dx[p]][y + dy[p]] != 'X') {
        dfs(opt + 1, x + dx[p], y + dy[p]);
        x += dx[p], y += dy[p];
    }
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == '*') {
                st_x = i, st_y = j;
                map[i][j] = '.';
            }
        }
    }

    cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        cin >> dir[i];
    }

    dfs(0, st_x, st_y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << map[i][j];
        }
        cout << "\n";
    }
    return 0;
}