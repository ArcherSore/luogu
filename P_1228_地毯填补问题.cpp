#include <iostream>
using namespace std;

void solve(int a, int b, int n, int x, int y) {
    if (n == 1) return;
    
    n /= 2;
    if (x <= a + n - 1 && y <= b + n - 1) {
        printf("%d %d 1\n", a + n, b + n);
        solve(a, b, n, x, y);
        solve(a, b + n, n, a + n - 1, b + n);
        solve(a + n, b, n, a + n, b + n - 1);
        solve(a + n, b + n, n, a + n, b + n);
    } else if (x <= a + n - 1 && y >= b + n) {
        printf("%d %d 2\n", a + n, b + n - 1);
        solve(a, b + n, n, x, y);
        solve(a, b, n, a + n - 1, b + n - 1);
        solve(a + n, b, n, a + n, b + n - 1);
        solve(a + n, b + n, n, a + n, b + n);
    } else if (x >= a + n && y <= b + n - 1) {
        printf("%d %d 3\n", a + n - 1, b + n);
        solve(a, b, n, a + n - 1, b + n - 1);
        solve(a, b + n, n, a + n - 1, b + n);
        solve(a + n, b, n, x, y);
        solve(a + n, b + n, n, a + n, b + n);
    } else {
        printf("%d %d 4\n", a + n - 1, b + n - 1);
        solve(a, b, n, a + n - 1, b + n - 1);
        solve(a, b + n, n, a + n - 1, b + n);
        solve(a + n, b, n, a + n, b + n - 1);
        solve(a + n, b + n, n, x, y);
    }
}

int main() {
    int k, x, y;
    cin >> k >> x >> y;
    int n = 1 << k;
    solve(1, 1, n, x, y);
    return 0;
}