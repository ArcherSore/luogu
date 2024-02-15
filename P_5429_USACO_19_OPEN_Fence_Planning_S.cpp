#include <iostream>
#include <vector>
using namespace std;

int top, bottom, l, r;

void dfs(int lvl, vector<pair<int, int>> &cow, vector<vector<int>> &G, vector<int> &vis) {
    if (vis[lvl]) return;
    vis[lvl] = 1;
    for (auto v : G[lvl]) {
        top = max(top, cow[v].first);
        bottom = min(bottom, cow[v].first);
        l = min(l, cow[v].second);
        r = max(r, cow[v].second);
        dfs(v, cow, G, vis);
    }
    return;
}

int main() {
    int n, m, x, y;
    cin >> n >> m;
    vector<pair<int, int>> cow(n + 1);
    vector<vector<int>> G(n + 1);
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        cow[i] = {x, y};
    }

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    long long ans = 4e8 + 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue; 
        top = cow[i].first, bottom = cow[i].first, l = cow[i].second, r = cow[i].second;
        dfs(i, cow, G, vis);
        // printf("l = %d, r = %d, t = %d, b = %d\n", l, r, top, bottom);
        ans = min(ans, 1LL * 2 * (r - l + top - bottom));
    }
    cout << ans << endl;
    return 0;
}