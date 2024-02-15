#include <iostream>
#include <string>
using namespace std;

bool _less(string &s, int i, int ans) {
    int n = s.size();
    for (int j = 0; j < n; j++) {
        if (s[(i + j) % n] != s[(ans + j) % n]) {
            return s[(i + j) % n] > s[(ans + j) % n];
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, ans = 0;
        string s;
        cin >> s;
        n = s.size();
        for (int i = 1; i < n; i++) {
            if (!_less(s, i, ans)) {
                ans = i;
            }
        }
        // cout << ans << endl;
        for (int i = 0; i < n; i++) {
            cout << s[(ans + i) % n];
        }
        cout << endl;
    }
    return 0;
}