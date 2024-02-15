#include <iostream>
using namespace std;

typedef long long LL;

const int MOD = 1e9 + 7;

void getNext(const string &s) {
    int n = s.size();
    int next[n] = {0}, num[n] = {0};
    int j = 0;
    num[1] = 1;

    for (int i = 1; s[i]; i++) {
        while (j && s[i] != s[j]) j = next[j];
        if (s[i] == s[j]) j += 1;
        next[i + 1] = j;
        num[i + 1] = num[j] + 1;
        

        // int x = i, cnt = 0;
        // while (next[x] != -1) {
        //     if (next[x] < (i + 1) / 2) {
        //         cnt++;
        //     }
        //     x = next[x];
        // }
        // ans = (ans * (cnt + 1)) % MOD;
    }

    j = 0;
    LL ans = 1;
    for (int i = 1; s[i]; i++) {
        while (j && s[i] != s[j]) j = next[j];
        if (s[i] == s[j]) j += 1;
        while (j > (i + 1) / 2) j = next[j];
        ans = (ans * 1LL * (num[j] + 1)) % MOD;
    }

    cout << ans << '\n';
    return;
}

int main() {
    int n;
    cin >> n;
    string s;
    while (n--) {
        cin >> s;
        getNext(s);
    }
    return 0;
}