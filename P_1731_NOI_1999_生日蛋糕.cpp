#include <iostream>
#include <cmath>
using namespace std;

int N, M;
int ans = 2e4;
int h[20], r[20];
int minV[20], minS[20];

inline int cube(int x) {
    return x * x * x;
}

inline int sqare(int x) {
    return x * x;
}

void dfs(int lvl, int S, int V) {
    // cout << V << endl;
    if (V + minV[lvl - 1] > N) return;
    if (S + minS[lvl - 1] >= ans) return;
    if (S + 2 * (N - V) / r[lvl + 1] >= ans) return; // !!!!!!! 最优性剪枝
    
    if (lvl == 0) {
        // cout << V << endl;
        if (V == N) ans = S;
        return;
    }

    for (int i = min((int)sqrt((N - V)), r[lvl + 1] - 1); i >= lvl; i--) {
        // 半径
        r[lvl] = i;
        for (int j = min((N - V) / (i * i), h[lvl + 1] - 1); j >= lvl; j--) {
            // 在i半径下的高度
            r[lvl] = i, h[lvl] = j;
            if (lvl != M) dfs(lvl - 1, S + 2 * i * j, V + i * i * j);
            else dfs(lvl - 1, S + 2 * i * j + i * i, V + i * i * j);
        }
    }
    return;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        minV[i] = minV[i - 1] + cube(i);
        minS[i] = minS[i - 1] + 2 * sqare(i);
    }
    // 第几层 已有的表面积 已有的体积 上一层的半径 上一层的高度
    // 从下到上枚举
    r[M + 1] = 20000, h[M + 1] = 20000;
    dfs(M, 0, 0);
    cout << (ans == 20000 ? 0 : ans) << endl; 
    return 0;
}