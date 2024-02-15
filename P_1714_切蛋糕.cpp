#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
int pre[MAXN] = {0};

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        pre[i] = pre[i - 1] + a;
    }

    deque<int> q;
    int ans = INT32_MIN;
    q.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (q.front() < i - m) {
            q.pop_front();
        }
        ans = max(ans, pre[i] - pre[q.front()]);
        while (!q.empty() && pre[q.back()] > pre[i]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    cout << ans << endl;
    return 0;
}