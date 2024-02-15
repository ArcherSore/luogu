#include <iostream>
using namespace std;

const int MAXN = 100000;
int a[MAXN + 5] = {0};

void get_digit() {
    for (int i = 1; i <= MAXN; i++) {
        int x = i, ans = x;
        while (x) {
            ans += x % 10;
            x /= 10;
        }
        if (!a[ans])
            a[ans] = i;
    }
    return;
}

int main() {
    get_digit();
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << a[x] << endl;
    }
    return 0;
}