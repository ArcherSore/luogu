#include <iostream>
#include <stack>
using namespace std;

char map[155][155];
int h[155], l[155], r[155];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }

    long long res = 0;
    for (int i = 1; i <= n; i++) {
        // 求h
        for (int j = 1; j <= n; j++) {
            h[j] = (map[i][j] == 'W') ? h[j] + 1 : 0;
        }
        // 求l
        stack<int> s1;
        h[0] = 0;
        s1.push(0);
        for (int j = 1; j <= n; j++) {
            while (!s1.empty()) {
                if (h[j] < h[s1.top()]) s1.pop();
                else break;
            }
            l[j] = s1.top();
            s1.push(j);
        }
        // 求r
        stack<int> s2;
        h[n + 1] = -1;
        s2.push(n + 1);
        for (int j = n; j >= 1; j--) {
            while (!s2.empty()) {
                if (h[j] <= h[s2.top()]) s2.pop();
                else break;
            }
            r[j] = s2.top();
            s2.push(j);
        }

        for (int j = 1; j <= n; j++) {
            res += h[j] * (j - l[j]) * (r[j] - j);
        }
    }
    cout << res << endl;
    return 0;
}