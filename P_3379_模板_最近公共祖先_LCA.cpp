#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 5e5 + 5;

int f[MAXN][20], depth[MAXN];
vector<vector<int>> G(MAXN);

void dfs(int u, int fa) {
    f[u][0] = fa, depth[u] = depth[fa] + 1;
    for (int i = 0; i <= 18; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    }

    for (int v : G[u]) {
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

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);

    for (int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(s, 0);
    
    int a, b;
    while (m--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", LCA(a, b));
    }
    return 0;
}