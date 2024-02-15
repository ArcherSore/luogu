#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
double a[MAXN], b[MAXN];
double pre_a[MAXN], pre_b[MAXN];

int d1[3] = {1, 0, 1};
int d2[3] = {0, 1, 1};

double cal(int p1, int p2) {
    return min(pre_a[p1] - p1 - p2, pre_b[p2] - p1 - p2);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &a[i], &b[i]);
    }
    sort(a + 1, a + n + 1, greater<double> ());
    sort(b + 1, b + n + 1, greater<double> ());
    for (int i = 1; i <= n; i++) {
        pre_a[i] = pre_a[i - 1] + a[i];
        pre_b[i] = pre_b[i - 1] + b[i];
    }

    int p1 = 0, p2 = 0;
    double res = -MAXN;
    while (1) {
        if (p1 > n || p2 > n) break;
        double tmp[3];
        double Max = -MAXN;
        int ind;
        for (int i = 0; i < 3; i++) {
            tmp[i] = cal(p1 + d1[i], p2 + d2[i]);
            if (tmp[i] > Max) {
                ind = i;
                Max = tmp[i];
            }
        }
        res = max(Max, res);
        p1 += d1[ind], p2 += d2[ind];
        // if (Max >= res) {
        //     p1 += d1[ind], p2 += d2[ind];
        //     res = Max;
        // } else {
        //     break;
        // }
        // printf("p1 = %d, p2 = %d, res = %.4lf\n", p1, p2, res);
    }
    printf("%.4lf\n", res < 0 ? 0 : res);
    return 0;
}