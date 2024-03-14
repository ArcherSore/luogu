#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<pair<int, int>> G[n + 1];
    vector<int> dis(n + 1, 0x3f3f3f3f);
    vector<int> vis(n + 1);
    // 存图，注意pair<dis[x], x>的方式来存
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({w, v});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    // 从s出发
    dis[s] = 0;
    q.push({dis[s], s});
    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        if (vis[x]) {
            continue;
        }
        vis[x] = 1;

        for (auto [w, y] : G[x]) {
            // 如果从dis[x] + x到y的距离小于dis[y]
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                q.push({dis[y], y});
            }
        }
    }
    // 找到s到任意点的距离
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " ";
    }
    return 0;
} 