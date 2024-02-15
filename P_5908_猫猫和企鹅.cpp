/*
    dfs 版本

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> G[MAXN];
int dis[MAXN], ans, n, m, d;

void dfs(int lvl, int in) {
    if (dis[lvl] <= d) ans++;
    for (int i = 0; i < G[lvl].size(); i++) {
        int v = G[lvl][i];
        if (v == in) continue; // 扫描的是进来的点
        dis[v] = dis[lvl] + 1;
        dfs(v, lvl);
    }
}

int main() {
    cin >> n >> d;
    for (int i = 0, a, b; i < n; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1, 0);
    cout << ans - 1;
    return 0;
}

*/

// bfs

#include <iostream>
#include <vector> 
#include <queue>
using namespace std;

const int MAXN = 1e5 + 5;

int n, d, dis[MAXN], fa[MAXN], ans;
vector<int> G[MAXN];
queue<int> q;

void bfs(int u) {
    q.push(u);
    while (!q.empty()) {
        int cur = q.front(); // 当前节点
        q.pop();
        if (dis[cur] <= d) ans++;
        for (int i = 0; i < G[cur].size(); i++) {
            int v = G[cur][i];
            if (v == fa[cur]) continue;
            fa[v] = cur;
            dis[v] = dis[cur] + 1;
            q.push(v);
        }
    }
}

int main() {
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    bfs(1);
    cout << ans - 1 << endl;
    return 0;
}