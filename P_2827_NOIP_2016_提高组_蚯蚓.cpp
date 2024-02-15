#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN];

int max_front(queue<int> *q, int delta) {
    int mx = INT32_MIN, mx_id;
    for (int i = 0; i < 3; i++) {
        if (!q[i].empty() && q[i].front() + delta > mx) {
            mx = q[i].front() + delta;
            mx_id = i;
        }
    }
    return mx_id;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, q, u, v, t;
    double p;
    queue<int> qu[3];
    cin >> n >> m >> q >> u >> v >> t;
    p = (double)u / v;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // cnm还要排序！！！样例怎么不给一个乱序的！！！！md
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = 1; i <= n; i++) {
        qu[0].push(a[i]);
    }
    
    int delta = 0;
    for (int i = 1; i <= m; i++) {
        int x, x1, x2, mx_id;
        mx_id = max_front(qu, delta);
        x = qu[mx_id].front() + delta;
        x1 = (int)(p * x) - delta - q, x2 = x - (int)(p * x) - delta - q;
        // printf("mx_id = %d, x = %d, x1 = %d, x2 = %d, delta = %d\n", mx_id, x, x1, x2, delta);
        qu[1].push(x1), qu[2].push(x2);
        qu[mx_id].pop();
        if (i % t == 0)
            cout << x << " ";
        delta += q;
    }
    cout << endl;
    // printf("1 = %ld, 2 = %ld, 3 = %ld\n", qu[0].size(), qu[1].size(), qu[2].size());
    long long cnt = qu[0].size() + qu[1].size() + qu[2].size();
    // printf("cnt = %d\n", cnt);
    for (long long i = 1; i <= cnt; i++) {
        long long mx_id = max_front(qu, delta), mx = qu[mx_id].front();
        if (i % t == 0) {
            cout << mx + delta << " ";
        }
        qu[mx_id].pop();
    }
    cout << endl;
    return 0;
}