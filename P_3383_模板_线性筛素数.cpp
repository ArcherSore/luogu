#include <iostream>
using namespace std;

const int MAXN = 1e8 + 5;

bool notPrime[MAXN]; // 标记是不是素数
int prime[MAXN]; // 存储素数

void primes(int n) {
    int m = 0; // 素数的个数
    for (int i = 2; i <= n; i++) {
        if (notPrime[i] == 0) {
            notPrime[i] = 1;
            prime[++m] = i; // i是素数
        }
        // 给当前的数i乘上一个素因子
        for (int j = 1; j <= m && i * prime[j] <= n; j++) {
            // i*prime[j]不是素数
            notPrime[i * prime[j]] = 1;
            // i能被prime[i]整除就break
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    int n, q, k = 0;
    scanf("%d%d", &n, &q);
    primes(n);
    while (q--) {
        scanf("%d", &k);
        printf("%d\n", prime[k]);
    }
    return 0;
}