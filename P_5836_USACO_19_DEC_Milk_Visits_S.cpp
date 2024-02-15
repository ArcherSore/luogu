#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
char color[MAXN];
int fu[MAXN], vis[MAXN];
vector<vector<int>> fa(MAXN);

void dfs(int lvl) {
    if (vis[lvl] || fa[lvl].empty()) return;

    vis[lvl] = 1;
    for (auto ch : fa[lvl]) {
        if (color[ch] == color[lvl]) {
            fu[ch] = fu[lvl];
        } else {
            fu[ch] = ch;
        }

        dfs(ch);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        fa[a].push_back(b);
    }
    fu[1] = 1;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }

    int a, b;
    char c;
    while (m--) {
        cin >> a >> b >> c;
        if (fu[a] == fu[b]) {
            if (color[a] == c || color[b] == c) cout << 1;
            else cout << 0;
        } else {
            cout << 1;
        }
    }
    return 0;
}