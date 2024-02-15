#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int h[MAXN];

long long max(long long a, long long b) {
    if (a > b) return a;
    return b;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
        }
        h[n + 1] = 0;

        stack<int> s;
        stack<int> w;
        long long ans = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (s.empty() || h[i] > s.top()) {
                s.push(h[i]);
                w.push(1);
            } else {
                int width = 0;
                while (!s.empty() && h[i] < s.top()) {
                    width += w.top();
                    ans = max(ans, (long long)width * s.top());
                    s.pop();
                    w.pop();
                }
                s.push(h[i]);
                w.push(width + 1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}