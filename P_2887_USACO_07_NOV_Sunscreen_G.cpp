#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

struct Cow {
    int l, r;
} cow[MAXN];

struct Lotion {
    int power, num;
} lotion[MAXN];

bool cmp1(const Cow &a, const Cow &b) {
    if (a.l != b.l)
        return a.l > b.l;
    return a.r > b.r;
}

bool cmp2(const Lotion &a, const Lotion &b) {
    return a.power > b.power;
}

int main() {
    int c, l;
    cin >> c >> l;
    for (int i = 0; i < c; i++) {
        cin >> cow[i].l >> cow[i].r;
    }
    sort(cow, cow + c, cmp1);
    for (int i = 0; i < l; i++) {
        cin >> lotion[i].power >> lotion[i].num;
    }
    sort(lotion, lotion + l, cmp2);

    int ans = 0;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            if (lotion[j].num == 0)
                continue;
            if (lotion[j].power >= cow[i].l && lotion[j].power <= cow[i].r) {
                ans += 1;
                lotion[j].num -= 1;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}