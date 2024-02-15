#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
long long pre[MAXN] = {0}, pre_mult[MAXN] = {0};

struct Stone {
    int w, v;
} stone[MAXN];

struct Query {
    int l, r;
} query[MAXN];

long long y, tmp, ans = INT64_MAX;
bool check(int W, int n, int m, long long s) {
    y = 0, tmp = 0;
    // init
    memset(pre, 0, sizeof(pre));
    memset(pre_mult, 0, sizeof(pre_mult));
    // prefix
    for (int j = 1; j <= n; j++) {
        if (stone[j].w >= W) {
            pre[j] = pre[j - 1] + 1;
            pre_mult[j] = pre_mult[j - 1] + stone[j].v;
        } else {
            pre[j] = pre[j - 1];
            pre_mult[j] = pre_mult[j - 1];
        }
    }
    // cal_y
    for (int i = 1; i <= m; i++) {
        y += (pre[query[i].r] - pre[query[i].l - 1]) * (pre_mult[query[i].r] - pre_mult[query[i].l - 1]);
    }
    tmp = llabs(y - s);
    return y > s;
}

int main() {
    int n, m;
    long long s;
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &stone[i].w, &stone[i].v);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &query[i].l, &query[i].r);
    }

    // binary search
    int mid, l = 0, r = MAXN;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid, n, m, s)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
        if (tmp < ans)
            ans = tmp;
    }
    cout << ans << endl;
    return 0;
}