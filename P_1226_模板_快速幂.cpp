#include <iostream>
using namespace std;

typedef long long LL;

// 非递归
LL fast_pow(LL a, LL b, LL p) {
    LL res = 1;
    while (b) {
        if (b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

// 递归
/*
LL fast_pow(LL a, LL b, LL p) {
    if (b == 0) return 1;
    LL res = fast_pow(a, b / 2);
    if (x % 2 == 0) return res * res % p;
    return res * res % p * a % p;
    
}
*/

int main() {
    LL a, b, p;
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << fast_pow(a, b, p);
    return 0;
}