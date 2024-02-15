#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
int c[MAXN] = {0};

map<pair<int, int>, bool> exist;

int main() {
    int n, id, h, r;
    cin >> n >> id >> h >> r;

    for (int i = 0, a, b; i < r; i++) {
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        if (exist[make_pair(a, b)])
            continue;
        for (int j = a + 1; j < b; j++) {
            c[j] -= 1;
        }
        exist[make_pair(a, b)] = true;
    }
    for (int i = 1; i <= n; i++) {
        cout << c[i] + h << endl;
    }
    return 0;
}