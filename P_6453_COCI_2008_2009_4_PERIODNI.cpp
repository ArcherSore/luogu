#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int N = 1e6;
const ll mod = 1e9 + 7;

vector<ll> fac(N + 1), invf(N + 1);

ll fpow(ll a, ll x) {
    ll res = 1;
    while (x) {
        if (x & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        x >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invf[N] = fpow(fac[N], mod - 2);
    for (int i = N - 1; i >= 0; i--) {
        invf[i] = invf[i + 1] * (i + 1) % mod;
    }
}

ll C(int n, int m) {
    if (n < m || m < 0) {
        return 0;
    }
    return fac[n] * invf[m] % mod * invf[n - m] % mod;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int root;
    vector<int> le(n + 1), ri(n + 1);
    auto build = [&]() -> void {
        stack<int> st;
        for (int i = 1; i <= n; i++) {
            int pre = 0;
            while (!st.empty() && a[i] < a[st.top()]) {
                pre = st.top();
                st.pop();
            }
            if (!st.empty()) {
                ri[st.top()] = i;
            }
            if (pre != 0) {
                le[i] = pre;
            }
            st.push(i);
        }
        while (st.size() > 1) {
            st.pop();
        }
        root = st.top();
    };
    build();

    // cerr << "1---\n";

    vector<vector<ll>> dp(n + 1, vector<ll> (k + 1));
    dp[0][0] = 1;
    vector<int> siz(n + 1);
    auto dfs = [&](auto &&self, int u, int p) -> void {
        if (u == 0) {
            return;
        }
        // cerr << "u = " << u << '\n';
        siz[u] = 1;
        self(self, le[u], u);
        siz[u] += siz[le[u]];
        self(self, ri[u], u);
        siz[u] += siz[ri[u]];

        vector<ll> g(k + 1);
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= i; j++) {
                g[i] = (g[i] + dp[le[u]][j] * dp[ri[u]][i - j] % mod) % mod;
            }
        }
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= i; j++) {
                dp[u][i] = (dp[u][i] + g[j] * C(a[u] - a[p], i - j) % mod * C(siz[u] - j, i - j) % mod * fac[i - j] % mod) % mod;
            }
        }
    };
    dfs(dfs, root, 0);
    cout << dp[root][k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}