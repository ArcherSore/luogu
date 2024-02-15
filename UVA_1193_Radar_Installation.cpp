#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Pos {
    double l, r;
} pos[MAXN];

bool cmp(const Pos &a, const Pos &b) {
    if (a.r != b.r)
        return a.r < b.r;
    return a.l < b.l;
}
void solve(int n, int d, int cnt) {
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        if (y > d) {
            printf("Case %d: %d\n", cnt, -1);
            return;
        }
        pos[i].r = x + sqrt(d * d - y * y);
        pos[i].l = x - sqrt(d * d - y * y);
    }
    sort(pos, pos + n, cmp);

    int ans = 1, end = pos[0].r;
    for (int i = 1; i < n; i++) {
        if (pos[i].l <= end) 
            continue;
        else {
            ans += 1;
            end = pos[i].r;
        }
    }
    printf("Case %d: %d\n", cnt, ans);
}

int main() {
    int n, d, cnt = 0;
    while (cin >> n >> d) {
        if (n == 0 && d == 0)
            break;
        cnt += 1;
        solve(n, d, cnt);
    }
    return 0;
}