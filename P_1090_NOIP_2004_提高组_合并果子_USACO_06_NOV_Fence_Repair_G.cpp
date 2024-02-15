#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;

int main() {
    int n;
    cin >> n;
    priority_queue<int> q;
    for (int i = 0, a; i < n; i++) {
        scanf("%d", &a);
        q.push(-a);
    }
    
    int ans = 0;
    while(q.size() != 1) {
        int a = -q.top();
        q.pop();
        int b = -q.top();
        q.pop();
        ans += (a + b);
        q.push(-(a + b));
    }
    cout << ans << endl;
    return 0;
}