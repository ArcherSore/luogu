#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int hi[10005] = {0};

int main() {
    int l, h, r, l_min = 10000, r_max = 0;
    while (cin >> l >> h >> r) {
        l_min = min(l_min, l), r_max = max(r_max, r);
        for (int i = l; i < r; i++) {
            hi[i] = max(hi[i], h);
        }
    }
    for (int i = l_min; i < r_max; i++) {
        if (hi[i] != hi[i - 1]) {
            if (hi[i] == 0)
                cout << i << " " << 0 << " ";
            else
                cout << i << " " << hi[i] << " ";
        }   
    }
    cout << r_max << " " << 0 << endl;
    return 0;
}