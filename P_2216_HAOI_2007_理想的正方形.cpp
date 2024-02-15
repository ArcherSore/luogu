#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1005;

int map[MAXN][MAXN];
int mx[MAXN][MAXN], mn[MAXN][MAXN];
int mx1[MAXN][MAXN], mn1[MAXN][MAXN];

void output(int a, int b, int n) {
    for (int i = n; i <= a; i++) {
        for (int j = n; j <= b; j++) {
            cout << mx1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = n; i <= a; i++) {
        for (int j = n; j <= b; j++) {
            cout << mn1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}

int main() {
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    // max
    for (int i = 1; i <= a; i++) {
        deque<int> q;
        q.push_back(0);
        map[i][0] = -1;
        for (int j = 1; j <= b; j++) {
            while (!q.empty() && map[i][j] > map[i][q.back()]) {
                q.pop_back();
            }
            q.push_back(j);
            while (!q.empty() && q.front() < j - n + 1) {
                q.pop_front();
            }
            if (j >= n) {
                mx[i][j] = map[i][q.front()];
            }
        }
    }
    for (int j = n; j <= b; j++) {
        deque<int> q;
        q.push_back(0);
        mx[0][j] = -1;
        for (int i = 1; i <= a; i++) {
            while (!q.empty() && mx[i][j] > mx[q.back()][j]) {
                q.pop_back();
            }
            q.push_back(i);
            while (!q.empty() && q.front() < i - n + 1) {
                q.pop_front();
            }
            if (i >= n) {
                mx1[i][j] = mx[q.front()][j];
            }
        }
    }

    // min
    for (int i = 1; i <= a; i++) {
        deque<int> q;
        q.push_back(0);
        map[i][0] = 1000000005;
        for (int j = 1; j <= b; j++) {
            while (!q.empty() && map[i][j] < map[i][q.back()]) {
                q.pop_back();
            }
            q.push_back(j);
            while (!q.empty() && q.front() < j - n + 1) {
                q.pop_front();
            }
            if (j >= n) {
                mn[i][j] = map[i][q.front()];
            }
        }
    }
    for (int j = n; j <= b; j++) {
        deque<int> q;
        q.push_back(0);
        mn[0][j] = 1000000005;
        for (int i = 1; i <= a; i++) {
            while (!q.empty() && mn[i][j] < mn[q.back()][j]) {
                q.pop_back();
            }
            q.push_back(i);
            while (!q.empty() && q.front() < i - n + 1) {
                q.pop_front();
            }
            if (i >= n) {
                mn1[i][j] = mn[q.front()][j];
            }
        }
    }
    // output(a, b, n);
    int res = 1000000005;
    for (int i = n; i <= a; i++) {
        for (int j = n; j <= b; j++) {
            res = min(res, mx1[i][j] - mn1[i][j]);
        }
    }
    cout << res << endl;
    return 0;
}