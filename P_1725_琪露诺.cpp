#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 201005;
const int INF = 0x3f3f3f3f;
int dp[MAXN], a[MAXN];

void output(int n) {
    for (int i = 0; i <= n; i++) {
        cout << i << " : " << dp[i] << endl;
    }
    return;
}

int main() {
    int n, l, r, k;
    cin >> n >> l >> r;
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    deque<int> q;
    dp[0] = 0;
    for (int i = 1; i < l; i++) {
        dp[i] = -INF;
    }
    for (int i = l; i <= n; i++) {
        // 单调队列
        // 存i - R ~ i - L的dp最大值的下标
        while (!q.empty() && dp[q.back()] < dp[i - l]) { 
            q.pop_back();
        }
        q.push_back(i - l);
        if (i - l - q.front() == r - l + 1) {
            q.pop_front();
        }
        // dp
        dp[i] = a[i] + dp[q.front()];

        // 
        // cout << "max = " << dp[q.front()] << ", dp" << i << " = " << dp[i] << "\n";
    }
    // output(n);
    int ans = -INF;
    for (int i = n - r + 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}