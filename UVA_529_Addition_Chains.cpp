#include <iostream>
#include <cstring>
using namespace std;

int ans[10010];
int n, m;
bool flag;

void print(int x) {
    for (int i = 0; i < x; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return;
}

void dfs(int p) {
    // 剪枝1
    if (ans[p - 1] > n) return;
    if (ans[p - 1] * (1 << (m - p)) < n) return;

    if (p == m) {
        if (ans[p - 1] == n) flag = 1;
        return;
    }
    for (int i = p - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            ans[p] = ans[i] + ans[j];
            dfs(p + 1);
            if (flag) return;
            ans[p] = 0;
        }
    }
}

void init() {
    for (int i = 1; i < m; i++) {
        ans[i] = 0;
    }
    flag = false;
}

int main() {
    ans[0] = 1;
    while (~scanf("%d", &n) && n) {
        if (n == 1) {
            printf("1\n");
            continue;
        }
        init();
        for (int i = 2; i <= n; i++) {
            m = i;
            dfs(1);
            // print(i);
            if (flag) {
                print(i);
                break;
            }
        }
    }
    return 0;
}