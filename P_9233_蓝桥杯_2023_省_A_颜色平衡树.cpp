#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;

vector<int> father(N), siz(N), son(N, -1);
vector<vector<int>> adj(N);

void dfs1(int u, int fa) {
    father[u] = fa;
    siz[u] = 1;
    for (auto v : adj[u]) {
        if (v == fa) {
            continue;
        }
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

vector<int> c(N);
vector<int> colorCnt(N), colorNum(N);
vector<bool> balanced(N);

void effect(int u) {
    colorNum[colorCnt[c[u]]]--;
    colorCnt[c[u]]++;
    colorNum[colorCnt[c[u]]]++;
    for (auto v : adj[u]) {
        if (v == father[u]) {
            continue;
        }
        effect(v);
    }
}

void cancel(int u) {
    colorNum[colorCnt[c[u]]]--;
    colorCnt[c[u]]--;
    colorNum[colorCnt[c[u]]]++;
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
    colorNum[colorCnt[c[u]]]--;
    colorCnt[c[u]]++;
    colorNum[colorCnt[c[u]]]++;
    for (auto v : adj[u]) {
        if (v == father[u] || v == son[u]) {
            continue;
        }
        effect(v);
    }
    if (siz[u] == colorCnt[c[u]] * colorNum[colorCnt[c[u]]]) {
        balanced[u] = true;
    }
    if (keep == 0) {
        cancel(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int fa;
        cin >> c[i] >> fa;
        fa--;
        if (fa != -1) {
            adj[fa].push_back(i);
        }
    }
    dfs1(0, -1);
    colorNum[0] = n;
    dfs2(0, 0);

    int res = 0;
    for (bool is : balanced) {
        if (is) {
            res++;
        }
    }
    cout << res << '\n';
    
    return 0;
}