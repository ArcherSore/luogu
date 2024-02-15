#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 5;

struct Cow {
    int beg, end, id;
} cow[MAXN];
int ans[MAXN], last[MAXN]; // the min end time in j_th fence 

bool cmp(const Cow &a, const Cow &b) {
    if (a.beg != b.beg)
        return a.beg < b.beg;
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &cow[i].beg, &cow[i].end);
        cow[i].id = i;
    }
    sort(cow + 1, cow + n + 1, cmp);

    int cnt = 0; // num of fence
    for (int i = 1; i <= n; i++) {
        int pos = -1;
        for (int j = 1; j <= cnt; j++) {
            if (cow[i].beg > last[j]) {
                // can use the fence
                pos = j;
                break;
            }
        }
        if (pos == -1) {
            // no existed fence is ok
            cnt += 1;
            pos = cnt;
        }
        last[pos] = cow[i].end;
        ans[cow[i].id] = pos;

    }
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}