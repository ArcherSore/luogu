#include <iostream>
using namespace std;

const int MAXN = 1005;
const int MAXM = 205;
const int MOD = 1000000007;

int dp[2][MAXM][MAXM][2];
char s[MAXN], t[MAXM];

int main() {
    int N, M, K;
    cin >> N >> M >> K >> s + 1 >> t + 1;
    
    // init
    dp[0][0][0][0] = dp[1][0][0][0] = 1;

    // dp
    int ind = 1;
    for (int i = 1; i <= N; i++, ind ^= 1) {
        for (int j = 1; j <= M; j++) {
            for (int p = 1; p <= K; p++) {
                dp[ind][j][p][0] = (dp[ind ^ 1][j][p][0] + dp[ind ^ 1][j][p][1]) % MOD;
                if (s[i] == t[j]) {
                    dp[ind][j][p][1] = ((dp[ind ^ 1][j - 1][p - 1][0] + dp[ind ^ 1][j - 1][p - 1][1]) % MOD + dp[ind ^ 1][j - 1][p][1]) % MOD;                   
                } else {
                    dp[ind][j][p][1] = 0;
                }
            }
        }
    }
    cout << (dp[N & 1][M][K][0] + dp[N & 1][M][K][1]) % MOD << endl;
    return 0;
}