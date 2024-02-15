#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 25;
int edge[MAXN][MAXN] = {0};
int vis[MAXN];
int n, m, ans = 0;

void dfs(int x, int dis) {
    for (int i = 1; i <= n; i++) {
        if (edge[x][i] > 0 && !vis[i]) {
            vis[i] = 1;
            dfs(i, dis + edge[x][i]);
        }
    }
    ans = max(ans, dis);
    vis[x] = 0;
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0, x, y, w; i < m; i++) {
        cin >> x >> y >> w;
        edge[x][y] = w;
        edge[y][x] = w;
    }
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        vis[i] = 1;
        dfs(i, 0);
    }
    cout << ans << endl;
    return 0;
}