#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 15;
int v[MAXN][MAXM];
map<string, int> id;
int cnt;

int get_id(string &s) {
    if (id.count(s) == 0) {
        id[s] = cnt;
        cnt++;
    }
    // cout << id.size() << endl;
    return id[s];
}

void is_PNF(int n, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            map<pair<int, int>, int> group;
            for (int k = 0; k < n; k++) {
                if (group.count(make_pair(v[k][i], v[k][j])) == 0) {
                    group[make_pair(v[k][i], v[k][j])] = k;
                } else {
                    cout << "NO\n" << group[make_pair(v[k][i], v[k][j])] + 1 << " " << k + 1 << "\n" << i + 1 << " " << j + 1 << "\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
    return;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        cnt = 0;
        id.clear();
        getchar();
        for (int i = 0; i < n; i++) {
            string s;
            for (int j = 0; j < m - 1; j++) {
                getline(cin, s, ',');
                v[i][j] = get_id(s);
            }
            getline(cin, s, '\n');
            v[i][m - 1] = get_id(s);
        }
        is_PNF(n, m);
    }
    return 0;
}