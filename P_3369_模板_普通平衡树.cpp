#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int inf = 1e9;

mt19937 rng(random_device{}());

inline double rand_() {
    uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

const int N = 100001;

int cnt = 0, head = 0;
int key[N], keycnt[N], le[N], ri[N], siz[N];
double pri[N];

void up(int i) {
    siz[i] = siz[le[i]] + siz[ri[i]] + keycnt[i];
}

int leftRotate(int i) {
    int r = ri[i];
    ri[i] = le[r];
    le[r] = i;
    up(i), up(r);
    return r;
}

int rightRotate(int i) {
    int l = le[i];
    le[i] = ri[l];
    ri[l] = i;
    up(i), up(l);
    return l;
}

int add(int i, int num) {
    if (i == 0) {
        key[++cnt] = num;
        keycnt[cnt] = siz[cnt] = 1;
        pri[cnt] = rand_();
        return cnt;
    }
    if (key[i] == num) {
        keycnt[i]++;
    } else if (key[i] > num) {
        le[i] = add(le[i], num);
    } else {
        ri[i] = add(ri[i], num);
    }
    up(i);
    if (le[i] != 0 && pri[le[i]] > pri[i]) {
        return rightRotate(i);
    }
    if (ri[i] != 0 && pri[ri[i]] > pri[i]) {
        return leftRotate(i);
    }
    return i;
}

void add(int num) {
    head = add(head, num);
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(le[i], num);
    } else {
        return siz[le[i]] + keycnt[i] + small(ri[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (siz[le[i]] >= x) {
        return index(le[i], x);
    } else if (siz[le[i]] + keycnt[i] < x) {
        return index(ri[i], x - siz[le[i]] - keycnt[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return -inf;
    }
    if (key[i] >= num) {
        return pre(le[i], num);
    } else {
        return max(key[i], pre(ri[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return inf;
    }
    if (key[i] <= num) {
        return post(ri[i], num);
    } else {
        return min(key[i], post(le[i], num));
    }
}

int post(int num) {
    return post(head, num);
}

int remove(int i, int num) {
    if (key[i] < num) {
        ri[i] = remove(ri[i], num);
    } else if (key[i] > num) {
        le[i] = remove(le[i], num);
    } else {
        if (keycnt[i] > 1) {
            keycnt[i]--;
        } else {
            if (le[i] == 0 && ri[i] == 0) {
                return 0;
            } else if (le[i] != 0 && ri[i] == 0) {
                i = le[i];
            } else if (le[i] == 0 && ri[i] != 0) {
                i = ri[i];
            } else {
                if (pri[le[i]] >= pri[ri[i]]) {
                    i = rightRotate(i);
                    ri[i] = remove(ri[i], num);
                } else {
                    i = leftRotate(i);
                    le[i] = remove(le[i], num);
                }
            }
        }
    }
    up(i);
    return i;
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        head = remove(head, num);
    }
}

void clear() {
    for (int i = 0; i <= cnt; i++) {
        key[i] = keycnt[i] = le[i] = ri[i] = siz[i] = 0;
        pri[i] = 0.0;
    }
    cnt = head = 0;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << '\n';
        } else if (op == 4) {
            cout << index(x) << '\n';
        } else if (op == 5) {
            cout << pre(x) << '\n';
        } else {
            cout << post(x) << '\n';
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