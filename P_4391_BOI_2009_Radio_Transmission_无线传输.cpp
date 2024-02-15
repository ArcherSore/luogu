#include <iostream>
using namespace std;

const int MAXN = 1e6 + 5;

int nxt[MAXN];

void getNext(const string &s) {
    int len = s.size();
    nxt[0] = -1;
    int j = -1;
    for (int i = 1; s[i]; i++) {
        while (j != -1 && s[i] != s[j + 1]) j = nxt[j];
        if (s[i] == s[j + 1]) j += 1;
        nxt[i] = j;
    }
    return;
}

int KMP(const string &s, const string &t) {
    int len = t.size(), j = -1;
    for (int i = 0; s[i]; i++) {
        while (j != -1 && s[i] != t[j + 1]) j = nxt[j];
        if (s[i] == t[j + 1]) j += 1;
        if (t[j + 1] == 0) return i - len + 1;
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    getNext(s);

    // for (int i = 0; i < n; i++) {
    //     if (nxt[i] != -1) {
    //         string tmp = s.substr(0, nxt[i] + 1);
    //         while ((int)tmp.size() <= n) {
    //             tmp += tmp;
    //         }
    //         if (KMP(tmp, s) != -1) {
    //             cout << nxt[i] + 1;
    //             // cout << s.substr(0, nxt[i] + 1) << endl;
    //             break;
    //         }
    //     }
    // }
    cout << n - nxt[n - 1] - 1;
    return 0;
}