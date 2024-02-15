#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int tag[MAXN];

void solve(int n) {
    while (1) {
        stack<int> s;
        int a = 1, b = 1; // a:指向压入的数字 b:指向目标数组
        for (int i = 1; i <= n; i++) {
            cin >> tag[i];
            if (tag[i] == 0) {
                cout << "\n";
                return;
            }
        }
        int ok = 1;
        while (b <= n) {
            if (a == tag[b]) {
                a++, b++;
            } else if (!s.empty() && s.top() == tag[b]) {
                s.pop();
                b++;
            } else if (a <= n) {
                s.push(a++);
            } else {
                ok = 0;
                break;
            }
        }
        if (ok) cout << "Yes\n";
        else cout << "No\n";
    }
    return;
}

int main() {
    int n;
    while (cin >> n && n) {
        solve(n);
    }
    return 0;
}