#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5e3 + 5;

struct Point {
    int x, y;
} p[MAXN];

bool cmp1(const Point &a, const Point &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> p[i].x >> p[i].y;
    }
    p[k++] = {0, 0};
    p[k++] = {0, m};
    p[k++] = {n, 0};
    p[k++] = {n, m};
    
    sort(p, p + k, cmp1);

    int ans = 0;
    for (int i = 0; i < k; i++) {
        int up = n, down = 0;
        // 左往右
        for (int j = i + 1; j < k; j++) {
            // 只枚举在down~up范围内的点
            if (p[j].x <= up && p[j].x >= down) {
                ans = max(ans, (p[j].y - p[i].y) * (up - down));
                if (p[i].x == p[j].x) {
                    // 如果平行后面不必继续找了（左右两个障碍点和up&down已经固定矩形了），再往下面积都是0
                    break;
                }
                if (p[j].x > p[i].x) {
                    up = min(up, p[j].x);
                } else {
                    down = max(down, p[j].x);
                }
            }
        }
        // 右往左
        up = n, down = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (p[j].x <= up && p[j].x >= down) {
                ans = max(ans, (p[i].y - p[j].y) * (up - down));
                if (p[i].x == p[j].x) {
                    break;
                } 
                if (p[j].x > p[i].x) {
                    up = min(up, p[j].x);
                } else {
                    down = max(down, p[j].x);
                }
            }
        }
    }

    sort(p, p + k, cmp2);
    for (int i = 1; i < k; i++) {
        ans = max(ans, m * (p[i].x - p[i - 1].x));
    }
    cout << ans << endl;
    return 0;
}