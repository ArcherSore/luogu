#include <iostream>
using namespace std;

int sudoku[9][9];
int row[9], col[9], grid[9]; // 二进制数
// int num_row[9], num_col[9], num_grid[9]; // 每行/列/格填了几个数
int ind[1 << 9]; // 二进制数的hash
int cnt[1 << 9]; // 二进制数中含有1的个数

bool dfs(int num) {
    if (num == 0) return true;
    // 找到棋盘上能填的可能性最少的位置x, y
    int can_place = 9, x, y;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j]) continue;
            int p = row[i] & col[j] & grid[i / 3 * 3 + j / 3];
            if (p == 0) return false; // 没有能填的了
            if (can_place > cnt[p]) {
                can_place = cnt[p];
                x = i, y = j;
            }
        }
    }

    int p = row[x] & col[y] & grid[x / 3 * 3 + y / 3];
    while (p) {
        int val = ind[-p & p];
        p -= (-p & p);
        
        sudoku[x][y] = val + 1;
        row[x] -= (1 << val);
        col[y] -= (1 << val);
        grid[x / 3 * 3 + y / 3] -= (1 << val);
        if (dfs(num - 1)) return true;
        
        sudoku[x][y] = 0;
        row[x] += (1 << val);
        col[y] += (1 << val);
        grid[x / 3 * 3 + y / 3] += (1 << val);
    }
    return false;
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
    int tot = 0; // 要填的数
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
            if (sudoku[i][j] == 0) {
                tot++;
            }
            else {
                row[i] -= 1 << (sudoku[i][j] - 1);
                col[j] -= 1 << (sudoku[i][j] - 1);
                grid[i / 3 * 3 + j / 3] -= 1 << (sudoku[i][j] - 1);

                // num_row[i]++, col[j]++, grid[i / 3 * 3 + j / 3]++;
            }
        }
    }
    
    dfs(tot);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}