#include <iostream>
#include <algorithm>
using namespace std;

int n, ans;
int a[70];
int vis[70], nxt[70];

bool dfs(int num, int len, int t, int l, int last) {
    if (t > num) {
        ans = len;
        return true;
    }
    if (len == l) {
        return dfs(num, len, t + 1, 0, 0);
    }
    int fail = 0; // 上一个尝试失败的木棍长度
    for (int i = last; i < n; i++){
        if (!vis[i] && a[i] + l <= len && fail != a[i]) {
            vis[i] = 1;
            if (dfs(num, len, t, a[i] + l, i + 1)) return true;
            vis[i] = 0;
            fail = a[i];
            i = nxt[i];
            // 如果空木棍就失败 or 已经拼好了不必用跟多木根来拼
            if (l == 0 || l + a[i] == len) return false;
        }
    }
    return false;
}

int main() {
    int sum = 0, val = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        val = max(val, a[i]);
    }
    sort(a, a + n, greater<int>());

    // 预处理next数组
    nxt[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i + 1] == a[i]) {
            nxt[i] = nxt[i + 1];
        } else {
            nxt[i] = i;
        }
    }

    for (int len = val; len <= sum; len++) {
        if (sum % len == 0) {
            // 目标棒子的个数 目标棒子的长度 在拼第几根棒子 这根棒子拼了多长 上一根木根的下标
            if (dfs(sum / len, len, 1, 0, 0)) break;
        }
    }
    cout << ans << endl;
    return 0;
}