#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int d[MAXN][MAXN] = {{0}}, e[MAXN][MAXN] = {{0}};

int main() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (int i = x1; i <= x2; i++) {
            d[i][y1]++;
            d[i][y2 + 1]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            e[i][j] = e[i][j - 1] + d[i][j];
            cout << e[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}