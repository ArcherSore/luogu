#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int a[MAXN], b[MAXN];
struct Data {
    // 压入的值和时间
    int x;
    int time;
};
map<int, int> num; // 存数字为i的个数

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        num[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    sort(a, a + n);
    sort(b, b + n, greater<int> ());

    stack<Data> s;
    int tm = 0, cnt = 0; // 记录时间和弹出的个数
    unsigned long long ans = 0;
    
    for (int i = 0; i < n; i) {
        int num_p = num[a[i]];
        while (num_p--) {
            // 压入所有相同数
            tm++;
            s.push({a[i], tm});
            i++;
        }
        // 弹出顶部
        Data p = s.top();
        s.pop();
        ans += 1ull * b[cnt++] * (tm - p.time);
    }
    while (!s.empty()) {
        Data p = s.top();
        s.pop();
        ans += 1ull * b[cnt++] * (tm - p.time);
        // cout << ans << endl;
    }
    cout << ans << endl;
    return 0;
}