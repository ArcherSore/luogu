#include <iostream>
using namespace std;

const int MAXN = 2005;
string word[MAXN];
int f[MAXN] = {0};

bool is_prefix(int j, int i) {
    if (word[j].size() >= word[i].size())
        return false;
    for (int k = 0; word[j][k]; k++) {
        if (word[j][k] != word[i][k])
            return false;
    }
    return true;
}
int main() {
    int n, ans =  0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> word[i];
    }
    for (int i = 0; i < n; i++) {
        f[i] = 1;
        for (int j = 0; j < i; j++) {
            if (is_prefix(j, i)) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
    return 0;
}