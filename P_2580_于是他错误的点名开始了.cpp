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

const int MAXN = 1e4 + 5; 

int nxt[MAXN * 50][26], cnt;
int flag[MAXN * 50], vis[MAXN * 50];

void insert(string &s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - 'a';
        if (!nxt[p][ind]) {
            nxt[p][ind] = ++cnt;
        }
        p = nxt[p][ind];
    }
    flag[p] = 1;
}

int find(string &s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - 'a';
        if (!nxt[p][ind]) {
            return 0;
        }
        p = nxt[p][ind];
    }
    if (!flag[p]) {
        return 0;
    } else {
        return ++vis[p];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert(s);
    }
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        int op = find(s);
        // cout << op << '\n';
        if (op == 0) {
            cout << "WRONG\n";
        } else if (op == 1) {
            cout << "OK\n";
        } else {
            cout << "REPEAT\n";
        }
    }
    return 0;
}