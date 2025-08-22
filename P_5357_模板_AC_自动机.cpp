#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int fail;
        std::array<int, ALPHABET> next;
        Node() : len{0}, fail{0}, next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        // t[0] is the virtual root, t[1] is the actual root node
        t.assign(2, Node());
        // The virtual root jumps to the root node for any letter
        t[0].next.fill(1);
        t[0].len = -1;
    }
    
    // Create a new node and return its index
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    // Insert a pattern string and return the index of the node corresponding to its last character
    int add(const std::string &a) {
        int p = 1;
        for (auto c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    // Build the fail pointers
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].fail].next[i];
                } else {
                    t[t[x].next[i]].fail = t[t[x].fail].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    
    // Query the transition result after node p goes through letter x
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    // Query the fail pointer of node p
    int fail(int p) {
        return t[p].fail;
    }
    
    // Query the depth of node p
    int len(int p) {
        return t[p].len;
    }
    
    // Return the total number of nodes
    int size() {
        return t.size();
    }
};

void solve() {
    int n;
    cin >> n;
    AhoCorasick ac;
    vector<string> pat(n);
    vector<int> end(n);
    for (int i = 0; i < n; i++) {
        cin >> pat[i];
        end[i] = ac.add(pat[i]);
    }
    ac.work();
    
    string s;
    cin >> s;
    int m = ac.size();
    vector<int> times(m);
    for (int i = 0, u = 1; i < s.size(); i++) {
        u = ac.next(u, s[i] - 'a');
        times[u]++;
    }
    vector<vector<int>> adj(m);
    for (int i = 1; i < m; i++) {
        adj[ac.fail(i)].push_back(i);
    }
    auto dfs = [&](auto &&self, int u) -> void {
        for (int v : adj[u]) {
            self(self, v);
            times[u] += times[v];
        }
    };
    dfs(dfs, 1);

    for (int i = 0; i < n; i++) {
        cout << times[end[i]] << '\n';
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