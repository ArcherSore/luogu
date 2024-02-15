#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAXN = 1e6 + 5;

int map[256];
int fa[MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int a, int b) {
    int aa = find(a), bb = find(b);
    fa[aa] = bb;
}

int main() {
    memset(map, -1, sizeof(map));
    int n;
    cin >> n;
    string s, t;
    cin >> s;

    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }

    int nxt[n];
    nxt[0] = -1;
    int j = -1;
    LL ans = 0;
    for (int i = 1; s[i]; i++) {
        while (j != -1 && s[i] != s[j + 1]) j = nxt[j];
        if (s[i] == s[j + 1]) j += 1;
        nxt[i] = j;

        // if (nxt[i] != -1) {
        //     if (map[s[i]] == -1)
        //         map[s[i]] = nxt[i];
        //     ans += (LL)(i - map[s[i]]);
        // }
        if (nxt[i] != -1) {
            merge(i, nxt[i]);
            ans += (LL)(i - find(i));
        }

        // if (nxt[i] != -1) {
        //     int x = nxt[i];
        //     while (nxt[x] != -1) {
        //         x = nxt[x];
        //     }
        // }
    }
    cout << ans << '\n';

    // for (char c = 'a'; c <= 'z'; c++) {
    //     cout << map[c] << " ";
    // }
    
    // for (int i = 0; i < n; i++) {
    //     cout << nxt[i] << " ";
    // }
    return 0;
}