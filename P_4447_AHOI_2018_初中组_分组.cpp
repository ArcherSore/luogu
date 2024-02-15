#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN];
struct Node {
    int len, last;
    bool operator< (const Node &a) const {
        return this->len > a.len;
    }
};

int main() {
    int n;
    cin >> n;
    priority_queue<Node> q;
    queue<Node> tmp;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);

    int ans = n;
    for (int i = 0; i < n; i++) {
        if (a[i] != a[i - 1] && i != 0) {
            while (!tmp.empty()) {
                q.push(tmp.front());
                tmp.pop();
            }
        }
        int flag = 0;
        while (!q.empty()) {
            Node top = q.top();
            q.pop();
            if (top.last == a[i] - 1) {
                // 继续组队
                flag = 1;
                tmp.push({top.len + 1, a[i]});
                break;
            } else {
                // 结算
                ans = min(ans, top.len);
            }
        }
        // new node
        if (!flag) {
            tmp.push({1, a[i]});
        }
    }

    while(!tmp.empty()) {
        q.push(tmp.front());
        tmp.pop();
    }
    while (!q.empty()) {
        Node top = q.top();
        q.pop();
        ans = min(ans, top.len);
    }
    
    cout << ans << endl;
    return 0;
}