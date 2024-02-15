#include <iostream>
#include <cstring>
using namespace std;

int ok[20][20][5];
int dp[205][205][5];
char s[205];

int to_num(char c) {
    if (c == 'W') return 1;
    if (c == 'I') return 2;
    if (c == 'N') return 3;
    if (c == 'G') return 4;
    return 0;
}

int main() {
    int n[5];
    for (int i = 1; i <= 4; i++) {
        cin >> n[i];
    }
    for (int i = 1; i <= 4; i++) {
        for (int k = 1; k <= n[i]; k++) {
            char a, b;
            cin >> a >> b;
            ok[to_num(a)][to_num(b)][i] = 1;
        }
    }

    cin >> (s + 1);
    int l = strlen(s + 1);
    // cout << l << endl;
    for (int i = 1; i <= l; i++) {
        dp[i][i][to_num(s[i])] = 1;
    }

    for (int len = 2; len <= l; len++) {
        for (int i = 1; i <= l - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (int x = 1; x <= 4; x++) {
                    for (int y = 1; y <= 4; y++) {
                        for (int z = 1; z <= 4; z++) {
                            if (dp[i][k][y] && dp[k + 1][j][z] && ok[y][z][x])
                                dp[i][j][x] = 1;
                        }
                    }
                }
            }
        }
    }

    int flag = 1;
    if (dp[1][l][1]) {
        flag = 0;
        cout << 'W';  
    } 
    if (dp[1][l][2]) {
        flag = 0;
        cout << 'I';  
    }
    if (dp[1][l][3]) {
        flag = 0;
        cout << 'N';  
    } 
    if (dp[1][l][4]) {
        flag = 0;
        cout << 'G';  
    } 
    if (flag) cout << "The name is wrong!";
    return 0;
}