#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    int op, x;
    priority_queue<int, vector<int>, greater<int>> q;
    while (n--) {
        cin >> op;
        if (op == 1) {
            cin >> x;
            q.push(x);
        } else if (op == 2) {
            cout << q.top() << '\n';
        } else {
            q.pop();
        }
    }
    return 0;
}