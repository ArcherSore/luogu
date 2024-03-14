#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 1e4 + 10;

using PII = pair<int, int>;

int n, m, s, f;
vector<PII> G[MAXN];

void dijkstra() {
    vector<int> vis(n + 1);
    vector<int> dis(n + 1, 0x3f3f3f3f);
    priority_queue<PII, vector<PII>, greater<PII>> h;
    dis[s] = 0;
    h.push({dis[s], s});

    while (!h.empty()) {
        auto [d, x] = h.top();
        h.pop();
        if (vis[x]) {
            continue;
        }
        vis[x] = 1;

        for (auto [y, w] : G[x]) {
            if (dis[y] > max(dis[x], w)) {
                dis[y] = max(dis[x], w);
                h.push({dis[y], y});
            }
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     cout << dis[i] << '\n';
    // }
    cout << dis[f] << '\n';
}

int main() {
    cin >> n >> m >> s >> f;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    dijkstra();

    return 0;
}