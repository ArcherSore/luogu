#include <iostream>
#include <stack>
using namespace std;

const int MAXN = 1010;

char s[MAXN][MAXN];
int h[MAXN], l[MAXN], r[MAXN]; 

int main() {
    int n, m;
    cin >> n >> m;
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
        stack<int> s1, s2;
        h[0] = 0, h[m + 1] = -1;
        s1.push(0), s2.push(m + 1);
        // 求h
        for (int j = 1; j <= m; j++) {
            h[j] = (s[i][j] == '*') ? 0 : h[j] + 1;
        }
        // 求l
        for (int j = 1; j <= m; j++) {
            while (!s1.empty()) {
                if (h[j] < h[s1.top()]) s1.pop();
                else break;
            }
            l[j] = s1.top();
            s1.push(j);
        }
        // 求r
        for (int j = m; j >= 1; j--) {
            while (!s2.empty()) {
                if (h[j] <= h[s2.top()]) s2.pop();
                else break;
            }
            r[j] = s2.top();
            s2.push(j);
        }
        // // 
        // for (int j = 1; j <= m; j++) {
        //     printf("h = %d, l = %d, j = %d\n", h[j], l[j], r[j]);
        // }
        // printf("\n");
        // // 
        for (int j = 1; j <= m; j++) {
            res += h[j] * (j - l[j]) * (r[j] - j);
        }
    }
    cout << res << endl;
    return 0;
}