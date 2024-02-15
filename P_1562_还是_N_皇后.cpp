#include <iostream>
using namespace std;

char mp[20][20];
int ind[1 << 20];

int ans = 0;
inline int lowbit(int x) {
    return -x & x;
}
void dfs(int i, int t1, int t2, int t3, int n) {
    // t1 列 t2 左斜线 t3 右斜线
    if (i > n) {
        ans++;
        return;
    }
    int can_place = t1 & t2 & t3;
    while (can_place) {
        int p = lowbit(can_place);
        can_place -= p;
        if (mp[i][ind[p] + 1] == '.') continue;
        dfs(i + 1, t1 - p, ((t2 - p) >> 1) + (1 << (n - 1)), ((t3 - p) << 1) + 1, n);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mp[i][j];
        }
    }

    for (int i = 0; i <= n; i++) {
        ind[1 << i] = i;
    }
    
    int t = (1 << n) - 1;
    dfs(1, t, t, t, n);
    cout << ans << endl;
    return 0;
}