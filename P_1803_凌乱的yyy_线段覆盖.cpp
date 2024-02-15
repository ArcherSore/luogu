#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

struct Time {
    int str, end;
} arr[MAXN];

bool cmp(const Time &a, const Time &b) {
    if (a.end != b.end)
        return a.end < b.end;
    return a.str < b.str;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &arr[i].str, &arr[i].end);
    }
    sort(arr, arr + n, cmp);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int ends = arr[i].end;
        ans += 1;
        while (ends > arr[i + 1].str && i < n) {
            i += 1;
        }
    }
    cout << ans << endl;
    return 0;
}