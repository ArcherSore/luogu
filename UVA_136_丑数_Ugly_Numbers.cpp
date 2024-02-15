#include <bits/stdc++.h>
using namespace std;

int multi[3] = {2, 3, 5};

int main() {
    priority_queue<long long, vector<long long>, greater<long long> > q;
    set<long long> s;
    q.push(1);
    s.insert(1);
    for (int i = 1; i < 1500; i++) {
        long long x = q.top();
        q.pop();
        for (int j = 0; j < 3; j++) {
            long long tmp = x * multi[j];
            if (s.count(tmp) == 0) {
                s.insert(tmp);
                q.push(tmp);
            }
        }
    }
    long long ans = q.top();
    cout << "The 1500'th ugly number is " << ans << ".\n";
    return 0;
}