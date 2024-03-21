#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <stack>
#include <set>
#include <map>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct Plan {
    int l, r;
    bool operator<(const Plan& other) const {
        return r < other.l;
    }
};

void solve() {
    int n;
    cin >> n;
    set<Plan> s;
    while (n--) {
        char opt;
        cin >> opt;
        if (opt == 'A') {
            int l, r, num = 0;
            cin >> l >> r;
            auto it = s.find({l, r});
            while (it != s.end()) {
                num++;
                s.erase(it);
                it = s.find({l, r});
            }
            s.insert({l, r});
            cout << num << '\n';
        } else {
            cout << s.size() << '\n';
        }
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}