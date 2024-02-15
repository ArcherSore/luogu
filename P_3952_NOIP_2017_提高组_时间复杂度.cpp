#include <iostream>
#include <stack>
#include <set>
using namespace std;

bool cmp(string &a, string &b) {
    if (a.size() < b.size() || b == "n") return false;
    else if (a.size() > b.size()) return true;
    else return a > b;
}

void solve() {
    int L;
    string s;
    cin >> L >> s;
    stack<char> st; // 判断是否error
    set<string> alpha; // 判断变量是否重复

    int max_times = 0; // 记录复杂度n的次数
    int times = 0;
    bool flag = true; // 嵌套循环仍然成立
    bool error = false;
    for (int i = 0; i < L; i++) {
        char c1;
        string c2, c3, c4;
        cin >> c1;
        if (c1 == 'F') {
            cin >> c2 >> c3 >> c4;
        }

        if (c1 == 'F') {
            st.push('F');
            if (alpha.count(c2)) {
                cout << "ERR\n";
                error = true;
            } else {
                alpha.insert(c2);
            }

            if (c3 == "n" || cmp(c3, c4)) {
                flag = false;
                continue;
            }
            else {
                if (c4 == "n") {
                    if (flag) {
                        times += 1;
                    }
                }
            }
        } else {
            if (st.empty()) {
                cout << "ERR\n";
                error = true;                
            }
            st.pop();
            if (st.empty()) {
                max_times = max(max_times, times);
                times = 0;
                flag = true;
            }
        }
    }
    if (error) {
        return;
    }
    if (!st.empty()) {
        cout << "ERR\n";
        return;
    } else {
        if (s[2] == '1') {
            if (max_times == 0) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
            return;
        } else {
            if (s[4] == max_times + '0') {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
            return;
        }
    }
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}