#include <bits/stdc++.h>
using namespace std;

#define MASK(n) ((1 << (n + 1)) - 2)

unordered_map<int, int> ind; // 位权到位置的映射
int total_ans = 3;
int arr[20];

void print(int n) {
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << " ";
        cout << arr[i];
    }
    cout << "\n";
    total_ans -= 1;
    return;
}

int dfs(int i, int t1, int t2, int t3, int n) {
    // 分配第i个皇后
    if (i > n) {
        if (total_ans) print(n);
        return 1;
    }
    int ans = 0;
    for (int t = t1; t; t -= (-t & t)) {
        // 获得可用的第一个位置
        int j = ind[-t & t];
        if ((t2 & (1 << (i + j - 1))) && (t3 & (1 << (i - j + n)))) {
            // 如果正斜线和反斜线都能够使用
            arr[i] = j; // 第i行第j列放置一个点
            ans += dfs(i + 1, t1 ^ (1 << j), t2 ^ (1 << (i + j - 1)), t3 ^ (1 << (i - j + n)), n);
            // 异或操作将最后一位1变为0
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    // 初始化哈希表
    for (int i = 0; i < 2 * n; i++) {
        ind[1 << i] = i;
    }
    // e.g. n = 6; MASK = 1111110
    int ans = dfs(1, MASK(n), MASK(2 * n - 1), MASK(2 * n - 1), n);
    cout << ans << endl;
    return 0;
}