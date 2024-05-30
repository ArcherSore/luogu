// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int MAXN = 3e6 + 5;

struct Trie {
    int next[MAXN][62], cnt;
    int val[MAXN];

    int code(char c) {
        if ('a' <= c && c <= 'z') {
            return c - 'a';
        } else if ('A' <= c && c <= 'Z') {
            return c - 'A' + 26;
        } else {
            return c - '0' + 52;
        }
    }

    void insert(string &s) {
        int p = 0;
        for (int i = 0; s[i]; i++) {
            int ind = code(s[i]);
            if (!next[p][ind]) {
                next[p][ind] = ++cnt;
            }
            p = next[p][ind];
            val[p] += 1;
        }
    }

    int find(string &s) {
        int p = 0;
        for (int i = 0; s[i]; i++) {
            int ind = code(s[i]);
            if (!next[p][ind]) {
                return 0;
            }
            p = next[p][ind];
        }
        return val[p];
    }

    void clear() {
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < 62; j++) {
                next[i][j] = 0;
            }
        }
        for (int i = 0; i < cnt; i++) {
            val[i] = 0;
        }
        cnt = 0;
    }
};

void solve(Trie &tr) {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        tr.insert(s);
    }
    while (q--) {
        string s;
        cin >> s;
        cout << tr.find(s) << '\n';
    }
    tr.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;

    Trie tr;
    while (T--) {
        solve(tr);
    }

    return 0;
}