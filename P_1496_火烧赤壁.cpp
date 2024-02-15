#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e4 + 5;

struct Line {
    int l, r;
} line[MAXN];

bool cmp(const Line &a, const Line &b) {
    if (a.l != b.l)
        return a.l < b.l;
    return a.r < b.r;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &line[i].l, &line[i].r);
    }
    sort(line, line + n, cmp);
    int ans = 0, str = INT32_MIN, end = INT32_MIN, flag = 0;
    for (int i = 0; i < n; i++) {
        if (str < line[i].l && end > line[i].r) {
            flag = 1;
            continue;
        }
        if (end < line[i].l) {
            ans += (end - str);
            str = line[i].l;
            end = line[i].r;
            flag = 0;
        } else {
            end = line[i].r;
            flag = 1;
        }
    }
    if (flag)
        ans += (end - str);
    cout << ans << endl;
    return 0;
}