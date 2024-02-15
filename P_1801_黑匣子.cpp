#include <iostream>
#include <queue>
using namespace std;

typedef long long LL;

int main() {
    int m, n;
    cin >> m >> n;
    vector<LL> a(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    queue<int> u;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        u.push(t);
    }

    priority_queue<LL> q_max;
    priority_queue<LL, vector<LL>, greater<LL>> q_min;
    int k = 0;
    for (int i = 1; i <= m; i++) {
        if (q_max.size() == k) {
            q_max.push(a[i]);
            q_min.push(q_max.top());
            q_max.pop();
        } else { // q_max.size() < k
            q_min.push(a[i]);
            q_max.push(q_min.top());
            q_min.pop();
        }
        
        int flag = 0; // 是否get多次
        while (i == u.front()) {
            if (flag) {
                q_max.push(q_min.top());
                q_min.pop();
            }
            
            cout << q_min.top() << '\n';
            u.pop();
            k++;

            flag = 1;
        }
    }
    return 0;
}