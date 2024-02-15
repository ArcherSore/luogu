#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

vector<pair<int, int>> G[MAXN];
int f[MAXN], vis[MAXN];

void dfs(int u, int val) {
    f[u] = val;
    vis[u] = 1;
    for (auto v : G[u]) {
        if (!vis[v.first]) {
            dfs(v.first, val ^ v.second);
        }
    }
    return;
}

int main() {
    int n, m;
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    dfs(1, 0);

    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << (f[a] ^ f[b]) << '\n';
    }

    return 0;
}