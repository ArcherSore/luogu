#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

struct Apple {
    int h, w;
} arr[MAXN];

bool cmp(const Apple &a, const Apple &b) {
    return a.w < b.w;
}

int main() {
    int n, s, a, b;
    cin >> n >> s >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].h >> arr[i].w;
    }
    sort(arr, arr + n, cmp);
    int ans = 0;
    for (int i = 0; i < n && s > 0; i++) {
        if (s - arr[i].w < 0) {
            break;
        }
        if (a + b >= arr[i].h) {
            ans += 1;
            s -= arr[i].w;
        } else {
            continue;
        }
    }
    cout << ans << endl;
    return 0;
}