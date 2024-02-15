#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

string P[205];
int dp[MAXN] = {0};

int main() {
    ios::sync_with_stdio(false);
    int t = 0;
    string s, T = " ";
    while (cin >> s && s != ".") {
        P[t++] = s;
    }
    while (cin >> s) {
        T += s;
    }

    int ans = 0;
    dp[0] = 1;
    for (int i = 1; i <= T.size(); i++) {
        for (int j = 0; j < t; j++) {
            // if (i - P[j].size() + 1 <= 0)
            //     continue;
            if (i >= P[j].size() && dp[i - P[j].size()] && T.substr(i - P[j].size() + 1, P[j].size()) == P[j]) {
                dp[i] = 1;
                ans = i;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}