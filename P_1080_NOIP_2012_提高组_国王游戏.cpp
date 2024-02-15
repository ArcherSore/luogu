#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
struct Data {
    int l, r;
} arr[MAXN];

string str(int x) {
    string ans = "";
    while (x) {
        ans += x % 10 + '0';
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int res[2 * MAXN];
string multiply(string a, string b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < a.size() + b.size(); i++) 
        res[i] = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            res[i + j] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = 0; i < a.size() + b.size(); i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    string ans = "";
    int flag = 1;
    for (int i = a.size() + b.size() - 1; i >= 0; i--) {
        if (res[i] == 0 && flag)
            continue;
        else {
            flag = 0;
            ans += (res[i] + '0');
        }
    }
    return ans;
}

int divs[2 * MAXN], div_res[2 * MAXN];
string division(string a, int b) {
    for (int i = 0; i < a.size(); i++) {
        divs[i] = 0;
        div_res[i] = 0;
    }
        
    for (int i = 0; i < a.size(); i++) {
        divs[i + 1] = a[i] - '0';
        int plus = 0;
        for (int i = 1; i <= a.size(); i++) {
            div_res[i] = (plus * 10 + divs[i]) / b;
            plus = (plus * 10 + divs[i]) % b;
        }
    }
    int lc = 1;
    while(div_res[lc] == 0 && lc < a.size())
        lc++;
    string ans = "";
    for (int i = lc; i <= a.size(); i++)
        ans += div_res[i] + '0';
    return ans;
}

string max(const string a, const string b) {
    if (a.size() != b.size())
        return a.size() > b.size() ? a : b;
    return a > b ? a : b;
}

bool cmp(const Data &a, const Data &b) {
    return a.l * a.r < b.l * b.r;
}

int main() {
    int n, l, r;
    cin >> n >> l >> r;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &arr[i].l, &arr[i].r);
    }
    sort(arr + 1, arr + n + 1, cmp);

    string T = str(l), ans = "0";
    for (int i = 1; i <= n; i++) {
        ans = max(ans, division(T, arr[i].r));
        T = multiply(T, str(arr[i].l));
        // cout << "ans = " << ans << ", T = " << T << endl;
    }
    cout << ans << endl;
    return 0;
}