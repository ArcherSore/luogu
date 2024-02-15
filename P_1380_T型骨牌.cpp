#include <iostream>
using namespace std;

int n, m;
int vis[15][15];
int cnt_put[15][15];
int dx[4][5] = {
    {-1, -1, -1, 0, 1},
    {1, 1, 1, 0, -1},
    {-1, 0, 1, 0, 0},
    {-1, 0, 1, 0, 0}
};
int dy[4][5] = {
    {-1, 0, 1, 0, 0},
    {-1, 0, 1, 0, 0},
    {-1, -1, -1, 0, 1},
    {1, 1, 1, 0, -1}
};

bool can_place(int x, int y, int dir) {
    for (int i = 0; i < 5; i++) {
        if (x + dx[dir][i] < 1 || x + dx[dir][i] > n || y + dy[dir][i] < 1 || y + dy[dir][i] > m || vis[x + dx[dir][i]][y + dy[dir][i]]) {
            return false;
        }
    }
    return true;
}

void place(int x, int y, int dir) {
    for (int i = 0; i < 5; i++) {
        vis[x + dx[dir][i]][y + dy[dir][i]] = 1;
    }
    return;
}

void undo(int x, int y, int dir) {
    for (int i = 0; i < 5; i++) {
        vis[x + dx[dir][i]][y + dy[dir][i]] = 0;
    }
    return;
}

int max_ans = 0;
void dfs(int x, int y, int num) {
    if (num + 1 < cnt_put[x][y]) 
        return;
    max_ans = max(max_ans, num);
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            // 枚举T中心位置
            if (vis[i][j]) continue;
            for (int p = 0; p < 4; p++) {
                // 枚举T的方向
                if (can_place(i, j, p)) {
                    place(i, j, p);
                    cnt_put[i][j] = max(cnt_put[i][j], num + 1); // 这个位置以前可放的最优解
                    dfs(i, j, num + 1);
                    undo(i, j, p);
                }
            }
        }
    }
    return;
}

int main() {
    cin >> n >> m;
    dfs(2, 2, 0);
    cout << max_ans << endl;
    return 0;
}