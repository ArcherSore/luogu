#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int dx[12] = {-2, -2, -2, -2, -1, 1, 2, 2, 2, 2, 1, -1};
int dy[12] = {-2, -1, 1, 2, 2, 2, 2, 1, -1, -2, -2, -2};

struct Node {
    int x, y;
    int step;
};

void bfs(int x, int y) {
    vector<vector<int>> vis(1000, vector<int> (1000, 0));
    queue<Node> q;
    q.push({x, y, 0});

    while (!q.empty()) {
        int step = q.front().step;
        int xx = q.front().x, yy = q.front().y;
        q.pop();
        // cout << xx << " " << yy << '\n';

        if (vis[xx][yy]) {
            continue;
        }
        vis[xx][yy] = 1;

        if (xx == 1 && yy == 1) {
            cout << step << '\n';
            return;
        }

        for (int i = 0; i < 12; i++) {
            int tx = xx + dx[i], ty = yy + dy[i];
            if (tx <= 0 || ty <= 0) {
                continue;
            }
            q.push({tx, ty, step + 1});
        }
    }
}

int main() {
	int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    bfs(x1, y1);
    bfs(x2, y2);
	return 0;
}