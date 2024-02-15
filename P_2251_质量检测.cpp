#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    deque<int> q;
    q.push_back(0);
    a[0] = 1e6 + 5;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && a[q.back()] > a[i]) {
            q.pop_back();
        }
        q.push_back(i);
        while (!q.empty() && q.front() < i - m + 1) {
            q.pop_front();
        }
        if (i >= m) {
            cout << a[q.front()] << '\n';
        }
    }
    return 0;
}