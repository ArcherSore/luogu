#include <iostream>
using namespace std;

const int d[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};
int dp[105][105];
char a[105], b[105];

int to_num(char x) {
    switch (x) {
    case 'A': return 0;
    case 'T': return 3;
    case 'C': return 1;
    case 'G': return 2;
    case '-': return 4;
    }
    return 0;
}

int val(char a, char b) {
    int x, y;
    x = to_num(a), y = to_num(b);
    return d[x][y];
}

int main() {
    int n, m;
    cin >> n >> (a + 1) >> m >> (b + 1);
    
    // init
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + val(a[i], '-');
    }
    for (int i = 1; i <= m; i++) {
        dp[0][i] = dp[0][i - 1] + val('-', b[i]);
    } 

    // dp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j - 1] + val(a[i], b[j]), max(dp[i - 1][j] + val(a[i], '-'), dp[i][j - 1] + val('-', b[j])));
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}