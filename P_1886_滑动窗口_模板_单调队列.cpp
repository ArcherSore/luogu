#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int a[MAXN];

void min_deque(int n, int k) {
    deque<int> q;
    q.push_front(0);
    a[0] = INT32_MAX;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && a[i] < a[q.back()]) {
            // 出现了更小值
            q.pop_back();
        }
        q.push_back(i);
        while (!q.empty() && q.front() < i - k + 1) {
            // 超出范围
            q.pop_front();
        }
        if (i >= k)
            cout << a[q.front()] << " ";
    }
    cout << endl;
    return;
}

void max_deque(int n, int k) {
    deque<int> q;
    q.push_front(0);
    a[0] = INT32_MIN;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && a[i] > a[q.back()]) {
            // 出现了更大值
            q.pop_back();
        }
        q.push_back(i);
        while (!q.empty() && q.front() < i - k + 1) {
            // 超出范围
            q.pop_front();
        }
        if (i >= k)
            cout << a[q.front()] << " ";
    }
    cout << endl;
    return;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    min_deque(n, k);
    max_deque(n, k);
    return 0;
}