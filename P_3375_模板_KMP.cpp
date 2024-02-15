#include <iostream>
using namespace std;

int *getNext(const string &t) {
    int len = t.size();
    int *next = (int *)malloc(sizeof(int) * len);
    next[0] = -1;
    int j = -1;
    for (int i = 1; t[i]; i++) {
        while (j != -1 && t[i] != t[j + 1]) j = next[j];
        if (t[i] == t[j + 1]) j += 1;
        next[i] = j;
    }
    return next;
}

void KMP(const string &s, const string &t) {
    int *next = getNext(t);
    int j = -1, len = t.size();
    for (int i = 0; s[i]; i++) {
        while (j != -1 && s[i] != t[j + 1]) j = next[j];
        if (s[i] == t[j + 1]) j += 1;
        if (t[j + 1] == 0) cout << i - len + 2 << "\n";
    }
    for (int i = 0; t[i]; i++) {
        if (i) printf(" ");
        printf("%d", next[i] + 1);
    }
    return;
}

int main() {
    string s, t;
    cin >> s >> t;
    KMP(s, t);
    return 0;
}