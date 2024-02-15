#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50000;

vector<int> G[MAXN];
int f[MAXN][20], depth[MAXN], pre[MAXN], res[MAXN];
int ans = 0;

void dfs(int u, int fa) {
    f[u][0] = fa, depth[u] = depth[fa] + 1;
    for (int i = 0; i  <= 18; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    }
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 18; ~i; i--) {
        if (depth[f[a][i]] >= depth[b]) {
            a = f[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 18; ~i; i--) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i];
            b = f[b][i];
        }
    }
    return f[a][0];
}

void get_max(int u, int fa) {
    for (int v : G[u]) {
        if (v == fa) continue;
        res[v] = res[u] + pre[v];
        ans = max(ans, res[v]);
        get_max(v, u);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);

    while (k--) {
        int a, b;
        cin >> a >> b;
        int t = LCA(a, b);
        pre[a]++, pre[b]++;
        pre[t]--, pre[f[t][0]]--;
    }
    get_max(1, 0);
    cout << ans << '\n';
    return 0;
}