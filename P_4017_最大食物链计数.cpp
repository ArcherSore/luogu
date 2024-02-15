#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 5e5 + 5;
const int mod = 80112002;
int indeg[MAXN], outdeg[MAXN], f[MAXN];
vector<vector<int> > g(MAXN);

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        indeg[y] += 1;
        outdeg[x] += 1;
        g[x].push_back(y);
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i]) continue;
        q.push(i);
        f[i] = 1;
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < g[now].size(); i++) {
            int next = g[now][i];
            indeg[next] -= 1;
            if (indeg[next] == 0) 
                q.push(next);
            f[next] += f[now];
            f[next] %= mod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (outdeg[i]) continue;
        ans += f[i];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}