#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int ind[MAXN]; // 第i个人属于第几个队伍

int main() {
    ios::sync_with_stdio(false);
    int t, cnt_test = 0;
    while (cin >> t && t) {
        cnt_test += 1;
        cout << "Scenario #" << cnt_test << endl;
        queue<int> q[t + 1]; // 0 : index 1~n : teammate
        for (int i = 1, n; i <= t; i++) { // 枚举队伍
            cin >> n;
            for (int j = 0, x; j < n; j++) {
                cin >> x;
                ind[x] = i;
            }
        }
        
        string s;
        while (cin >> s && s != "STOP") {
            if (s == "ENQUEUE") {
                int x;
                cin >> x;
                if (q[ind[x]].empty()) {
                    // new queue
                    q[0].push(ind[x]);
                }
                q[ind[x]].push(x);
            } else {
                int id = q[0].front();
                cout << q[id].front() << endl;
                q[id].pop();
                if (q[id].empty()) {
                    q[0].pop();
                }
            }
        }
        cout << endl;
    }
    return 0;
}