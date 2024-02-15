#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e4 + 5;
int fa[MAXN], head[MAXN], val[MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    int root = find(fa[x]);
    val[x] = val[x] + val[fa[x]];
    return fa[x] = root;
}

void merge(int a, int b, int t) {
    int aa = find(a), bb = find(b);
    if (aa == bb) return;
    val[aa] = t - val[a] + val[b];
    fa[aa] = bb;
    return;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 0; i < n; i++) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == 'M') {
            merge(a, b, 1);
        } else {
            if (find(a) == find(b)) {
                cout << abs(val[a] - val[b]);
            } else {
                cout << "-1\n";
            }
        }
    }
    return 0;
}