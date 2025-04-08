#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e5 + 1;

vector<int> father(N), siz(N), son(N, -1);
vector<vector<int>> adj(N);

void dfs1(int u, int fa) {
    father[u] = fa;
    siz[u] = 1;
    for (auto v : adj[u]) {
        if (v == fa) {
            continue;
        }
        father[v] = father[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
    }
    for (auto v : adj[u]) {
        if (v == fa) {
            continue;
        }
        if (son[u] == -1 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

vector<int> a(N);
vector<int> colorCnt(N), res(N);
int diffColor = 0;

void effect(int u) {
    if (++colorCnt[a[u]] == 1) {
        diffColor++;
    }
    for (auto v : adj[u]) {
        if (v == father[u]) {
            continue;
        } 
        effect(v);
    }
}

void cancel(int u) {
    if (--colorCnt[a[u]] == 0) {
        diffColor--;
    }
    for (auto v : adj[u]) {
        if (v == father[u]) {
            continue;
        } 
        cancel(v);
    }
}

void dfs2(int u, int keep) {
    for (auto v : adj[u]) {
        if (v == father[u] || v == son[u]) {
            continue;
        } 
        dfs2(v, 0);
    }
    if (son[u] != -1) {
        dfs2(son[u], 1);
    }
    if (++colorCnt[a[u]] == 1) {
        diffColor++;
    }
    for (auto v : adj[u]) {
        if (v == father[u] || v == son[u]) {
            continue;
        }
        effect(v);
    }
    res[u] = diffColor;
    if (keep == 0) {
        cancel(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(0, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dfs2(0, 0);

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        x--;
        cout << res[x] << '\n';
    }

    return 0;
}