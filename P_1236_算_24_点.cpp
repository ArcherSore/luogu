#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int a[4];
map<int, char> opt;

void print(int a, int b, int op, int res) {
    int mx = max(a, b), mn = min(a, b);
    cout << mx << opt[op] << mn << "=" << res << endl;
    return;
}

int cal(int a, int b, int op) {
    switch(op) {
        case 0: return a + b; break;
        case 1: {
            if (a <= b) 
                return 100;
            return a - b; 
            break;
        }
        case 2: return a * b; break;
        case 3: {
            if (a < b || a == 0 || b == 0 || a % b) return 100; 
            return a / b; 
            break;
        }
    }
    return 100;
}

int main() {
    opt[0] = '+', opt[1] = '-', opt[2] = '*', opt[3] = '/';
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    sort(a, a + 4);
    
    do {
        int sum;
        // ((a b) c) d
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    sum = cal(cal(cal(a[0], a[1], i), a[2], j), a[3], k);
                    if (sum == 24) {
                        int x = a[0], y = a[1], res = cal(x, y, i);
                        print(x, y, i, res);
                        x = res, y = a[2], res = cal(x, y, j);
                        print(x, y, j, res);
                        x = res, y = a[3], res = cal(x, y, k);
                        print(x, y, k, res);
                        return 0;
                    }
                }
            }
        }
        // (a, b) (c, d)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    sum = cal(cal(a[0], a[1], i), cal(a[2], a[3], j), k);
                    if (sum == 24) {
                        int x = cal(a[0], a[1], i), y = cal(a[2], a[3], j);
                        print(a[0], a[1], i, x);
                        print(a[2], a[3], j, y);
                        print(x, y, k, 24);
                        return 0;
                    }
                }
                
            }
        }
    } while (next_permutation(a, a + 4));
    cout << "No answer!" << endl;
    return 0;
}