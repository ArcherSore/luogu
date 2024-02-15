#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 2e6 + 5;

int a[MAXN];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    deque<int> q;
    q.push_front(0);
    a[0] = -1;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && a[i] > a[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
        while (!q.empty() && q.front() < i - k + 1) {
            q.pop_front();
        }
        if (i >= k) printf("%d\n", a[q.front()]);
    }
    return 0;
}