#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static const LL MOD  = 1000000007;
static const LL INV2 = 500000004;
static const LL INV3 = 333333336;
static const LL INV6 = 166666668;

struct Min25 {
    LL n, S;
    int num;
    vector<bool> is_comp;
    vector<LL> prime, sp1, sp2;
    vector<LL> w, g1, g2;
    vector<int> id1, id2;

    Min25(LL n_): n(n_), S(sqrtl(n_)) {
        pre(S);
        build();
    }

    LL solve() {
        // f(1)=1；如需修改 f(1)，请在此处调整 “+1”
        return add(calc(n, 0), 1);
    }

private:
    LL add(LL a, LL b) const { a += b; return a >= MOD ? a - MOD : a; }
    LL sub(LL a, LL b) const { a -= b; return a < 0   ? a + MOD : a; }
    LL mul(LL a, LL b) const { return (a % MOD) * (b % MOD) % MOD; }

    void pre(int lim) {
        is_comp.assign(lim+1, false);
        prime.assign(lim+1, 0);
        sp1.assign(lim+1, 0);
        sp2.assign(lim+1, 0);
        num = 0;
        is_comp[1] = true;
        for (int i = 2; i <= lim; ++i) {
            if (!is_comp[i]) {
                prime[++num] = i;
                sp1[num] = add(sp1[num-1], i);
                sp2[num] = add(sp2[num-1], mul(i,i));
            }
            for (int j = 1; j <= num && prime[j] * (LL)i <= lim; ++j) {
                is_comp[prime[j]*i] = true;
                if (i % prime[j] == 0) break;
            }
        }
    }

    void build() {
        id1.assign(S+1, 0);
        id2.assign(S+1, 0);
        for (LL i = 1, j; i <= n; i = j+1) {
            LL v = n / i; j = n / v;
            LL vm = v % MOD;
            w.push_back(v);
            LL t1 = mul(mul(vm, vm+1), INV2);        // ∑t
            g1.push_back(sub(t1, 1));                // −1
            LL t2 = mul(mul(mul(vm, vm+1), (2*vm+1)%MOD), INV6); // ∑t^2
            g2.push_back(sub(t2, 1));                // −1
            int idx = (int)w.size() - 1;
            if (v <= S) id1[v] = idx; else id2[n/v] = idx;
        }
        for (int i = 1; i <= num; ++i) {
            LL p = prime[i], p2 = p*p;
            for (int k = 0; k < (int)w.size() && p2 <= w[k]; ++k) {
                int kk = idx(w[k]/p);
                g1[k] = sub(g1[k], mul(p, sub(g1[kk], sp1[i-1])));
                g2[k] = sub(g2[k], mul(mul(p,p), sub(g2[kk], sp2[i-1])));
            }
        }
    }

    int idx(LL x) const { return x <= S ? id1[x] : id2[n/x]; }

    // f(p^e)=p^e*(p^e−1)；迁移到其他积性函数，仅修改此处
    LL f_pe(LL pe) const {
        LL m = pe % MOD;
        return mul(m, sub(m, 1));
    }

    LL calc(LL x, int y) {
        if (prime[y] >= x) return 0;
        int k = idx(x);
        LL res = sub(sub(g2[k], g1[k]), sub(sp2[y], sp1[y]));
        for (int i = y+1; i <= num && prime[i]*(LL)prime[i] <= x; ++i) {
            LL p = prime[i];
            for (LL pe = p, e = 1; pe <= x; pe *= p, ++e) {
                LL t = add(calc(x/pe, i), e > 1);
                res = add(res, mul(f_pe(pe), t));
            }
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LL n;
    cin >> n;
    Min25 solver(n);
    cout << solver.solve() << "\n";
    return 0;
}