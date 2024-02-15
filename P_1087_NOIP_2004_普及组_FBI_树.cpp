#include <iostream>
using namespace std;

int n;
const int MAXN = 2000;
char s[MAXN];

void BuildTree(int x, int y) {
    if (x < y) {
        BuildTree(x, (x + y) / 2);
        BuildTree((x + y + 1) / 2, y);
    }
    int zero = 0, one = 0;
    for (int i = x; i <= y; i++) {
        if (s[i] == '0') 
            zero += 1;
        if (s[i] == '1')
            one += 1;
    }
    if (zero == 0) cout << "I";
    else if (one == 0) cout << "B";
    else cout << "F";
    return;
}

int main() {
    cin >> n >> s + 1;
    BuildTree(1, 1 << n);
    return 0;
}