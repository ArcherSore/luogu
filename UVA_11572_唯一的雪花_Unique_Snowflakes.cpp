#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, ans = 0;
        cin >> n;
        set<int> v;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int p1 = 0, p2 = 1;
        v.insert(a[p1]);
        while (p1 < n && p2 < n) {
            if (v.find(a[p2]) == v.end()) {
                v.insert(a[p2]);
                p2++;
            } else {
                while (a[p1] != a[p2]) {
                    v.erase(a[p1]);
                    p1++;
                }
                p1++;
                p2++;
            }
            // cout << "p1 = " << p1 << " p2 = " << p2 << endl;
            ans = max(ans, (int)v.size());
        }
        cout << ans << endl;
    }
    return 0;
}