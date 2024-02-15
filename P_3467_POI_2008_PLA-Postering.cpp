#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    stack<int> s;
    int res = 0;
    for (int i = 0, w, h; i < n; i++) {
        cin >> w >> h;
        while (!s.empty() && s.top() >= h) {
            if (s.top() == h) res++;
            s.pop();
        }
        s.push(h);
    }
    cout << n - res << endl;
}