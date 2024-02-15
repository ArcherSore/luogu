#include <iostream>
using namespace std;

const int MAXN = 100005;
const int MOD = 10007;

int color[MAXN], number[MAXN];
int num[MAXN][2], pre[MAXN][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &number[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
        num[color[i]][i % 2]++;
        // 颜色为b[i]且编号为奇/偶的格子的数量
        pre[color[i]][i % 2] = (pre[color[i]][i % 2] + number[i]) % MOD;
        // 求符合上述要求的格子上面的数字之和
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res += i * (pre[color[i]][i % 2] + number[i] * (num[color[i]][i % 2] - 2) % MOD) % MOD;
        res %= MOD;
    }
    printf("%d\n", res);
    return 0;
}