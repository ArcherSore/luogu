#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
long long a[MAXN], b[MAXN];

int main() {
    int n;
    long long pos = 0, neg = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1) {
            b[i] = a[i];
        } else {
            b[i] = a[i] - a[i - 1];
            if (b[i] > 0) {
                pos += b[i];
            }
            if (b[i] < 0) {
                neg += b[i];
            }
        }
    }
    cout << max(pos, -neg) << endl << abs(pos + neg) + 1 << endl;
    return 0;
}