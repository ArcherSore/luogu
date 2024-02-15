#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 100005;
int indeg[MAXN] = {0}, exist[MAXN] = {0};
vector<vector<int> > g(MAXN);

int main() {
    int n, cnt = 0, max_n = 0; // 砸掉的数量
    cin >> n;
    for (int i = 1, x, t; i <= n; i++) {
        cin >> x >> t;
        exist[x] = 1; // x位置存在摄像头
        for (int j = 1, y; j <= t; j++) {
            cin >> y;
            indeg[y] += 1;
            g[x].push_back(y); // x摄像头监视y位置
        }
        max_n = max(max_n, x);
    }
    
    queue<int> q; 
    for (int i = 1; i <= max_n; i++) {
        if (exist[i] && indeg[i] == 0) {
            // 入度为0且该点有摄像头
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        cnt += 1;
        for (int i = 0; i < g[now].size(); i++) {
            int next = g[now][i];
            indeg[next] -= 1;
            if (exist[next] && indeg[next] == 0) {
                // 入度为0且该点有摄像头
                q.push(next);
            }
        }
    }
    if (cnt == n) 
        cout << "YES" << endl;
    else 
        cout << n - cnt << endl;
    return 0;
}