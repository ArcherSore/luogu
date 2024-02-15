#include <iostream>
using namespace std;

const int MAXN = 505;

int R, C, A, B;
int N[MAXN][MAXN], sum[MAXN][MAXN];

int check(int mid) {
    int horizontal = 0, vertical = 0;
    int last_x = 0, last_y = 0;
    for (int i = 1; i <= R; i++) {
        last_y = 0, vertical = 0;
        for (int j = 1; j <= C; j++) {
            if (sum[i][j] - sum[last_x][j] - sum[i][last_y] + sum[last_x][last_y] >= mid) {
                last_y = j;
                vertical += 1;
            }
        }
        if (vertical >= B) {
            // 已经切了够B
            horizontal++;
            last_x = i;
        }
    }
    return horizontal >= A;
}

int main() {
    cin >> R >> C >> A >> B;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> N[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + N[i][j];
        }
    }

    int l = 0, r = sum[R][C] / (A * B), mid, ans;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}