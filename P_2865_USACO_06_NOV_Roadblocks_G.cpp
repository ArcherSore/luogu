#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct Vertix {
    int dis, type, v;
    bool operator>(const Vertix& other) const {
        return dis > other.dis;
    }
};

void dijkstra(vector<vector<PII>> &G, vector<vector<int>> &dis, int n) {
    vector vis(n + 1, vector<int> (2));
    priority_queue<Vertix, vector<Vertix>, greater<Vertix>> h;
    dis[1][0] = 0;
    h.push({dis[1][0], 0, 1});

    while (!h.empty()) {
        auto [d, type, x] = h.top();
        h.pop();
        if (vis[x][type]) {
            continue;
        }
        vis[x][type] = 1;

        for (auto [y, w] : G[x]) {
            if (dis[y][0] > d + w) {
                dis[y][1] = dis[y][0];
                h.push({dis[y][1], 1, y});
                dis[y][0] = d + w;
                h.push({dis[y][0], 0, y});
            } else if (dis[y][1] > d + w && dis[y][0] != d + w) {
                // 次短路 > d + w 并且d + w不等于最短路！
                dis[y][1] = d + w;
                h.push({dis[y][1], 1, y});
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector G(n + 1, vector<PII> ());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    vector dis(n + 1, vector<int> (2, 0x3f3f3f3f));
    dijkstra(G, dis, n);

    cout << dis[n][1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}