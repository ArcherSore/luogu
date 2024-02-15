#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
struct Data {
    int t, f, h; 
} arr[MAXN];
int dp[2 * MAXN]; // 达到i高度时获得的最大生命值

bool cmp(const Data &a, const Data &b) {
    return a.t < b.t;
}

int main() {
    int D, G;
    cin >> D >> G;
    for (int i = 0; i < G; i++) {
        cin >> arr[i].t >> arr[i].f >> arr[i].h;
    }
    sort(arr, arr + G, cmp);

    dp[0] = 10; // 初始能活10h
    for (int i = 0; i < G; i++) {
        for (int j = D; j >= 0; j--) {
            if (dp[j] < arr[i].t)
                continue;
            if (j + arr[i].h >= D) {
                cout << arr[i].t << endl;
                return 0;
            }
            // 填
            // dp[j]表示前i-1件物品能站在高度j的最大生命值
            dp[j + arr[i].h] = max(dp[j + arr[i].h], dp[j]);
            // 吃
            dp[j] += arr[i].f;
        }
    }
    cout << dp[0] << endl; // 最长吃掉所有垃圾
    return 0;   
}