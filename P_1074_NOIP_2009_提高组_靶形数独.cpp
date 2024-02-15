#include <iostream>
using namespace std;

int sudoku[9][9];
int row[9], col[9], grid[9];
int ind[1 << 9], cnt[1 << 9]; // 二进制中含有1的个数
int score[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
};

int max_ans = 0, ans = 0;

void dfs(int lvl) {
    if (lvl == 0) {
        max_ans = max(max_ans, ans);
        return;
    }

    // 找到可填情况最少的位置
    int can_place = 9, x, y;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j]) continue;
            int p = row[i] & col[j] & grid[i / 3 * 3 + j / 3];
            if (p == 0) return;
            if (can_place > cnt[p]) {
                can_place = cnt[p];
                x = i, y = j;
            }
        }
    }

    // 从(x, y)开始枚举深搜
    int p = row[x] & col[y] & grid[x / 3 * 3 + y / 3];
    while(p) {
        int val = ind[-p & p];
        p -= (-p & p);

        sudoku[x][y] = val + 1;
        ans += score[x][y] * sudoku[x][y];
        row[x] -= (1 << val);
        col[y] -= (1 << val);
        grid[x / 3 * 3 + y / 3] -= (1 << val);

        dfs(lvl - 1);
        ans -= score[x][y] * sudoku[x][y];
        sudoku[x][y] = 0;
        row[x] += (1 << val);
        col[y] += (1 << val);
        grid[x / 3 * 3 + y / 3] += (1 << val);
    }
}

int main() {
    // pre
    int MASK = (1 << 9) - 1;
    for (int i = 0; i < 9; i++) {
        row[i] = col[i] = grid[i] = MASK;
        ind[1 << i] = i;
    }
    for (int i = 0; i < (1 << 9); i++) {
        for (int j = i; j; j -= (-j & j)) {
            cnt[i]++;
        }
    }
    // input & init
    int tot = 0; // 记录0的个数
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
            ans += sudoku[i][j] * score[i][j];
            if (sudoku[i][j]) {
                row[i] -= 1 << (sudoku[i][j] - 1);
                col[j] -= 1 << (sudoku[i][j] - 1);
                grid[i / 3 * 3 + j / 3] -= 1 << (sudoku[i][j] - 1);
            } else {
                tot++;
            }
        }
    }
    dfs(tot);
    cout << (max_ans == 0 ? -1 : max_ans) << endl;
    return 0;
}