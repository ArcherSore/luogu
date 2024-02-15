#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 0x7fffffff;
int a[MAXN], b[MAXN];
int dp[MAXN], pos[MAXN];


int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        dp[i] = INF;
    }

    int len = 0; 
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int l = 0, r = len, mid;
        if (pos[b[i]] > dp[len]) {
            dp[++len] = pos[b[i]];
        } else {
            while (l < r) {
                mid = (l + r) / 2;
                if (dp[mid] > pos[b[i]]) r = mid;
                else l = mid + 1;
            }
            dp[l] = min(pos[b[i]], dp[l]);
        }
    }
    cout << len;
    return 0; 
}