// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const int MAXN = 1e5 + 5;

vector<vector<PII>> G(MAXN);
int d[MAXN], vis[MAXN];
int nxt[32 * MAXN][2], cnt;

string to_str(int x) {
    string s;
    for (int i = 0; i <= 31; i++) {
        s.push_back((x & 1) + '0');
        x >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

void insert(string &s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - '0';
        if (!nxt[p][ind]) {
            nxt[p][ind] = ++cnt;
        }
        p = nxt[p][ind];
    }
}

int find(string &s) {
    int p = 0, ans = 0;
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - '0';
        if (nxt[p][1 - ind]) {
            p = nxt[p][1 - ind];
            ans += (1 << 31 - i);
        } else {
            p = nxt[p][ind];
        }
    }
    return ans;
}

void dfs(int u, int t) {
    vis[u] = 1;
    for (auto [v, w] : G[u]) {
        if (!vis[v]) {
            dfs(v, d[v] = d[u] ^ w);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int u, v, w;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    dfs(1, 0);

    vector<string> s(n);
    for (int i = 1; i <= n; i++) {
        s[i - 1] = to_str(d[i]);
        insert(s[i - 1]);
    } 
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, find(s[i]));
    }
    cout << res << '\n';
    return 0;
}