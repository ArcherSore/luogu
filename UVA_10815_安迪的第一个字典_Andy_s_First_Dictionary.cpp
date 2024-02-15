#include <bits/stdc++.h>
using namespace std;

set<string> dict;

int main() {
    string s, buf;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i])) {
                s[i] = tolower(s[i]);
            } else {
                s[i] = ' ';
            }
        }
        stringstream ss(s);
        while (ss >> buf) {
            dict.insert(buf);
        }
    }
    for (auto x : dict) {
        cout << x << endl;
    }
    return 0;
}