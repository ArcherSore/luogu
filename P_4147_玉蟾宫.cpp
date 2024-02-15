#include <iostream>
using namespace std;

const int MAXN = 1010;

char map[MAXN][MAXN];
int h[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN];

void output(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << l[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << r[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
            // init
            if (map[i][j] == 'F') {
                h[i][j] = 1;
                l[i][j] = r[i][j] = j;
            } 
        }
    }
    // output(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map[i][j] == 'F') {
                if (map[i - 1][j] == 'F') h[i][j] = h[i - 1][j] + 1;
                if (map[i][j - 1] == 'F') l[i][j] = l[i][j - 1];
            }
        }
        for (int j = m - 1; j >= 1; j--) {
            if (map[i][j] == 'F' && map[i][j + 1] == 'F') r[i][j] = r[i][j + 1];
        }
    }
    // output(n, m);
    for (int j = 1; j <= m; j++) {
        for (int i = 2; i <= n; i++) {
            if (map[i][j] == 'F' && map[i - 1][j] == 'F') {
                l[i][j] = max(l[i][j], l[i - 1][j]);
            }
            if (map[i][j] == 'F' && map[i - 1][j] == 'F') {
                r[i][j] = min(r[i][j], r[i - 1][j]);
            }
        }
    }
    // output(n, m);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = max(ans, h[i][j] * (r[i][j] - l[i][j] + 1));
        }
    }
    cout << 3 * ans << endl;
    return 0;
}