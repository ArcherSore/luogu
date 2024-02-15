#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
int a[MAXN], vis[MAXN];

int find_max(int cur, int n) {
    int max_id, maxn = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && abs(a[i] - a[cur]) > maxn) {
            max_id = i;
            maxn = abs(a[i] - a[cur]);
        }
    }
    return max_id;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];

    int jump = 0, cur = 0;
    long long ans = 0;
    a[0] = 0, vis[0] = 1;
    while (jump != n) {
        int j = find_max(cur, n);
        // cout << "j = " << j << endl;
        ans += (a[cur] - a[j]) * (a[cur] - a[j]);
        cur = j;
        jump += 1;
        vis[j] = 1;
    }
    cout << ans << endl;
    return 0;
}