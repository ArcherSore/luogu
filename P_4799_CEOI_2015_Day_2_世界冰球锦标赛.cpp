#include <iostream>
#include <algorithm>
using namespace std;

long long ticket[50];
long long n, m, k;
long long p[1 << 21];
long long res, cnt;

void dfs1(int lvl, long long s) {
    if (lvl >= k) {
        p[cnt++] = s;
        return;
    }

    dfs1(lvl + 1, s);
    if (ticket[lvl] + s <= m) {
        dfs1(lvl + 1, s + ticket[lvl]);
    }
    return;
}

void dfs2(int lvl, long long s) {
    if (lvl >= n) {
        // p + s <= m -> p <= m - s的位置
        long long pos = upper_bound(p, p + cnt, m - s) - p;
        res += pos;
        return;
    }

    dfs2(lvl + 1, s);
    if (ticket[lvl] + s <= m) {
        dfs2(lvl + 1, s + ticket[lvl]);
    }
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> ticket[i];
    }
    sort(ticket, ticket + n, greater<long long> ());
    k = n / 2;
    dfs1(0, 0);

    sort(p, p + cnt);
    // for (int i = 0; i < cnt; i++) {
    //     cout << p[i] << endl;
    // }

    dfs2(k, 0);

    cout << res << endl;
    return 0;
}