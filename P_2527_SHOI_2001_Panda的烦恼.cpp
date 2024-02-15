#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 2e9;

int main() {
    int n, k, maxn = 0;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        q.push(a[i]);
    }

    // vector<int> ans;
    int last = 0, cnt = 0;
    while (!q.empty()) {
        int tmp = q.top();
        q.pop();
        // printf("%d\n", tmp);
        if (tmp == last) continue;
        last = tmp;
        cnt++;
        if (cnt == k) {
            printf("%d\n", tmp);
            return 0;
        }
        for (auto p : a) {
            if (1LL * tmp * p > MAX) {
                continue;
            }
            q.push(tmp * p);
        }
    }
    return 0;
}