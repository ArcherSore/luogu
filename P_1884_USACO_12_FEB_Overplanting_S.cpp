#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 4010;
int a[MAXN][4]; // 存矩形左上角和右下角
int b[MAXN], c[MAXN];
int f[MAXN][MAXN]; // 差分数组
map<int, int> matrix;

int main() {
    int n;
    cin >> n;
    int btop = 0, ctop = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a[i][j];
            b[++btop] = a[i][j];
        }
    }
    // 离散化
    sort(b + 1, b + btop + 1);
    for (int i = 1; i <= btop; i++) {
        if (i == 1 || b[i] != b[i - 1]) {
            c[++ctop] = b[i];
            matrix[b[i]] = ctop;
        }
    }
    // 给关键数值标号
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = matrix[a[i][j]];
        }
    }
    // 矩形覆盖
    for (int i = 1; i <= n; i++) {
        for (int j = a[i][0]; j < a[i][2]; j++) {
            f[j][a[i][3]]++, f[j][a[i][1]]--;
        }
    }
    // 前缀和还原原序列
    for (int i = 1; i < ctop; i++) {
        for (int j = 1; j < ctop; j++) {
            f[i][j] += f[i][j - 1];
        }
    }
    LL ans = 0;
    for (int i = 1; i < ctop; i++) {
        for (int j = 1; j < ctop; j++) {
            if (f[i][j]) {
                ans += (LL)(c[i + 1] - c[i]) * (c[j + 1] - c[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}