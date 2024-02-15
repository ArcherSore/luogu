#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN];

int main() {
    string s;
    int k;
    cin >> s >> k;
    while (k--) {
        int flag = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] > s[i + 1]) {
                s.erase(i, 1);
                flag = 1;
                // cout << s << endl;
                break;
            }        
        }
        if (!flag)
            s.erase(s.size() - 1);
    }
    // 前导0...
    while (s[0] == '0' && s.size() > 1)  {
        s.erase(0, 1);
    }
    cout << s << endl;
    return 0;
}