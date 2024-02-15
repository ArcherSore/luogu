#include <iostream>
#include <unordered_map>
using namespace std;

int map[5][5];
unordered_map<int, int> ind;

// 按照顺序摆放
bool check(int x, int y, int val) {
    // 判断这个位置能不能放val
    if (x == 3 && y == 3 && (map[0][0] + map[0][3] + map[3][0] + val) != 34) return false; // 四角
    if (y == 3 && (map[x][0] + map[x][1] + map[x][2] + val) != 34) return false; // 行
    if (x == 3 && (map[0][y] + map[1][y] + map[2][y] + val) != 34) return false; // 列
    if (x == 1 && y == 1 && (map[0][0] + map[0][1] + map[1][0] + val) != 34) return false; // 左上2*2格子
    if (x == 1 && y == 3 && (map[0][2] + map[0][3] + map[1][2] + val) != 34) return false; // 右上格子
    if (x == 3 && y == 1 && (map[2][0] + map[2][1] + map[3][0] + val) != 34) return false; // 左下格子
    if (x == 3 && y == 3 && (map[2][2] + map[2][3] + map[3][2] + val) != 34) return false; // 右下格子
    if (x == 2 && y == 2 && (map[1][1] + map[1][2] + map[2][1] + val) != 34) return false; // 中间格子
    if (x == 3 && y == 0 && (map[0][3] + map[1][2] + map[2][1] + val) != 34) return false; // 副对角线
    if (x == 3 && y == 3 && (map[0][0] + map[1][1] + map[2][2] + val) != 34) return false; // 主对角线
    return true;
}

void output() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(int num, int x, int y, int t, int x0, int y0) {
    // 枚举第num个数 坐标(x, y) 能选数的状态 1的坐标(x0, y0)
    output();
    if (num == 17) {
        output();
        return;
    }

    // 如果这个位置是放1的(不知道怎么融入下面的判断)
    if (x == x0 && y == y0) {
        if (!check(x, y, 1)) return;
        map[x][y] = 1;
        if ((y + 1) == 4) {
            dfs(num + 1, x + 1, 0, t, x0, y0);
        } else {
            dfs(num + 1, x, y + 1, t, x0, y0);
        }
        map[x][y] = 0;
    }
    // 循环取出最后一个1 -> 枚举可选的数
    for (int i = t; i; i -= (-i & i)) {
        // 不能放继续下一个可选的数
        if (!check(x, y, ind[-i & i] + 1)) continue;
        map[x][y] = ind[-i & i] + 1;

        // 行末换行(x + 1)枚举
        if ((y + 1) == 4) {
            // t - (-i & i) -> 这个数放置之后的状态
            dfs(num + 1, x + 1, 0, t - (-i & i), x0, y0);
        } else {
            dfs(num + 1, x, y + 1, t - (-i & i), x0, y0);
        }

        map[x][y] = 0;
    }
    return;
}

int main() {
    freopen("output.txt", "w", stdout);
    int MASK = (1 << 15) - 1; // 111...111初始状态表示1~16能用
    for (int i = 0; i < 16; i++) {
        ind[1 << i] = i; // 二进制数到可用数字的映射
    }

    int x, y;
    cin >> x >> y;
    x -= 1, y -= 1; // 存储(0~3, 0~3)

    // 枚举第几个数 坐标(0, 0) 能选数的状态(1已经不能选了) 1的坐标(x, y)
    dfs(1, 0, 0, MASK - 1, x, y);

    return 0;
}