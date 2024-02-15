#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    stack<long long> s;
    long long ans = 0;
    for (auto x : h) {
        while (!s.empty()) {
            if (x >= s.top()) {
                s.pop();
            } else {
                break;
            }
        }
        ans += s.size();
        s.push(x);
    }
    cout << ans << endl;
    return 0;
}