#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int inf = 1e9;

const double ALPHA = 0.7;
const int MAXN = 100001;
int head = 0, cnt = 0;
vector<int> key(MAXN), keycnt(MAXN), le(MAXN), ri(MAXN);
vector<int> siz(MAXN), diff(MAXN), collect(MAXN);
int ci, top, father, side;
// 新建节点，返回编号
int newNode(int num) {
    key[++cnt] = num;
    le[cnt] = ri[cnt] = 0;
    keycnt[cnt] = siz[cnt] = diff[cnt] = 1;
    return cnt;
}
// 更新节点 i 的子树信息
void up(int i) {
    siz[i] = siz[le[i]] + siz[ri[i]] + keycnt[i];
    diff[i] = diff[le[i]] + diff[ri[i]] + (keycnt[i] > 0 ? 1 : 0);
}
// 中序遍历收集所有存在的节点编号
void inorder(int i) {
    if (i != 0) {
        inorder(le[i]);
        if (keycnt[i] > 0) {
            collect[++ci] = i;
        }
        inorder(ri[i]);
    }
}
// 由排序数组[collect[l], ..., collect[r]]重建一棵平衡子树，返回新根节点编号
int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int m = (l + r) / 2;
    int h = collect[m];
    le[h] = build(l, m - 1);
    ri[h] = build(m + 1, r);
    up(h);
    return h;
}
// 对不平衡的树进行重构
void rebuild() {
    if (top != 0) {
        ci = 0;
        inorder(top);
        if (ci > 0) {
            if (father == 0) {
                head = build(1, ci);
            } else if (side == 1) {
                le[father] = build(1, ci);
            } else {
                ri[father] = build(1, ci);
            }
        }
    }
}
// 判断节点i是否平衡
bool balance(int i) {
    return ALPHA * diff[i] >= max(diff[le[i]], diff[ri[i]]);
}

void add(int i, int f, int s, int num) {
    if (i == 0) {
        if (f == 0) {
            head = newNode(num);
        } else if (s == 1) {
            le[f] = newNode(num);
        } else {
            ri[f] = newNode(num);
        }
    } else {
        if (key[i] == num) {
            keycnt[i]++;
        } else if (key[i] > num) {
            add(le[i], i, 1, num);
        } else {
            add(ri[i], i, 2, num);
        }
        up(i);
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
}
// 插入一个数 num
void add(int num) {
    top = father = side = 0;
    add(head, 0, 0, num);
    rebuild();
}
// 统计以 i 为根的树中，小于 num 的元素个数
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
// 查询 num 的排名（即有多少数小于 num）+ 1
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
// 查询整棵树的第 x 小元素
int index(int x) {
    return index(head, x);
}
// 查询 num 的前驱（严格小于 num 的最大值）
int pre(int num) {
    int kth = getRank(num);
    if (kth == 1) {
        return -inf;
    } else {
        return index(kth - 1);
    }
}
// 查询 num 的后继（严格大于 num 的最小值）
int post(int num) {
    int kth = getRank(num + 1);
    if (kth == siz[head] + 1) {
        return inf;
    } else {
        return index(kth);
    }
}

void remove(int i, int f, int s, int num) {
    if (key[i] == num) {
        keycnt[i]--;
    } else if (key[i] > num) {
        remove(le[i], i, 1, num);
    } else {
        remove(ri[i], i, 2, num);
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
}
// 删除一个 num
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        top = father = side = 0;
        remove(head, 0, 0, num);
        rebuild();
    }
}

void clear() {
    for (int i = 0; i <= cnt; i++) {
        key[i] = keycnt[i] = le[i] = ri[i] = siz[i] = diff[i] = 0;
    }
    cnt = head = 0;
}

void solve() {
    int n;
    cin >> n;
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            add(x);
        } else if (opt == 2) {
            remove(x);
        } else if (opt == 3) {
            cout << getRank(x) << '\n';
        } else if (opt == 4) {
            cout << index(x) << '\n';
        } else if (opt == 5) {
            cout << pre(x) << '\n';
        } else {
            cout << post(x) << '\n';
        }
    }
    clear();
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