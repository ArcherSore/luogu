#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 10010;

using PII = pair<int, int>;
struct Node {
    int ver, dist, times;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

int n, m, k, s, f;
vector<PII> G[MAXN];

void dijkstra() {
    vector<vector<int>> vis(n + 1, vector<int> (11));
    vector<vector<int>> dis(n + 1, vector<int> (11, 0x3f3f3f3f));
    priority_queue<Node, vector<Node>, greater<Node>> h;
    dis[s][0] = 0;
    h.push({s, 0, 0});

    while (!h.empty()) {
        auto now = h.top();
        h.pop();
        int x = now.ver, d = now.dist, times = now.times;
        if (vis[x][times]) {
            continue;
        } 
        vis[x][times] = 1;

        for (auto [y, w] : G[x]) {
            if (times < k && dis[y][times + 1] > dis[x][times]) {
                // 可以免费通行
                dis[y][times + 1] = dis[x][times];
                h.push({y, dis[y][times + 1], times + 1});
            }
            if (dis[y][times] > dis[x][times] + w) {
                // 付费通行
                dis[y][times] = dis[x][times] + w;
                h.push({y, dis[y][times], times});
            }
        }
    }

    int res = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++) {
        res = min(res, dis[f][i]);
    }
    cout << res << '\n';
}

int main() {
    cin >> n >> m >> k >> s >> f;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
    
    dijkstra();

    return 0;
}