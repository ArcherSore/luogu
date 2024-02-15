#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 5;

struct Variant {
    int i, j, e;
} a[MAXN];
int b[2 * MAXN], c[2 * MAXN]; // b:存储i和j c:离散化i和j
int fa[2 * MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int xx = find(x), yy = find(y);
    if (xx != yy) fa[xx] = yy;
    return;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int btop = 0, ctop = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].i >> a[i].j >> a[i].e;
            b[++btop] = a[i].i;
            b[++btop] = a[i].j;
        }
        // 离散化
        sort(b + 1, b + btop + 1);
        for (int i = 1; i <= btop; i++) {
            if (i == 1 || b[i] != b[i - 1]) 
                c[++ctop] = b[i];
        }
        for (int i = 1; i <= n; i++) {
            a[i].i = lower_bound(c + 1, c + ctop + 1, a[i].i) - c;
            a[i].j = lower_bound(c + 1, c + ctop + 1, a[i].j) - c;
        }
        // 并查集
        for (int i = 1; i <= ctop; i++) {
            fa[i] = i;
        }
        for (int i = 1; i <= n; i++) {
            if (a[i].e == 1) {
                merge(a[i].i, a[i].j);
            }
        }
        int flag = 1;
        for (int i = 1; i <= n; i++) {
            if (a[i].e == 0) {
                if (find(a[i].i) == find(a[i].j)) {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}