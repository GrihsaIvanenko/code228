#include <bits/stdc++.h>

using namespace std;

const int MAXN = 524288;

int pr[MAXN], ran[MAXN];

int get(int x) {
    if (x == pr[x]) {
        return x;
    }
    return get(pr[x]);
}

vector<int> cash;

bool unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
        return false;
    }
    if (ran[a] < ran[b]) {
        swap(a, b);
    }
    cash.push_back(b);
    ran[a] = max(ran[a], ran[b] + 1);
    pr[b] = a;
    return true;
}

vector<int> anscash;

struct segtree {
    int lb, rb, mid;
    segtree *l = nullptr, *r = nullptr;
    vector<pair<int, int>> rebs;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void adde(int le, int re, pair<int, int> reb) {
        if (lb >= re || rb <= le) {
            return;
        }
        if (le <= lb && rb <= re) {
            rebs.push_back(reb);
            return;
        }
        l->adde(le, re, reb);
        r->adde(le, re, reb);
    }
    void print() {
        cout << lb << " " << rb << " : ";
        cout << "Rebs ";
        for (auto x : rebs) {
            cout << x.first + 1 << "<->" << x.second + 1 << " ";
        }
        cout << "end Rebs\n";
        if (l != nullptr) {
            l->print();
            r->print();
        }
    }
    int dfs(int ans) {
        int t = cash.size();
        for (auto x : rebs) {
            if (x.first != -1 && (get(x.first) != get(x.second))) {
                if (unite(x.first, x.second)) {
                    --ans;
                }
            }
        }
        if (rb - lb != 1) {
            ans = l->dfs(ans);
            ans = r->dfs(ans);
        } else if (rebs.size() == 1 && rebs.back().first == -1) {
            anscash.push_back(ans);
            return ans;
        }
        for (int i = cash.size() - 1; i >= t; --i) {
            if (get(pr[cash[i]]) == get(cash[i])) {
                ++ans;
            }
            pr[cash[i]] = cash[i];
        }
        cash.resize(t);
        return ans;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    map<pair<int, int>, vector<int>> mmop, mmcl;
    segtree *Node = new segtree(0, MAXN);
    for (int i = 0; i < m; ++i) {
        char it;
        cin >> it;
        if (it == '?') {
            Node->adde(i, i + 1, {-1, -1});
        } else {
            int v, u;
            cin >> v >> u;
            --v;
            --u;
            if (v > u) {
                swap(v, u);
            }
            if (it == '+') {
                mmop[{v, u}].push_back(i);
            } else {
                mmcl[{v, u}].push_back(i);
            }
        }
    }
    for (auto x : mmop) {
        for (unsigned i = 0; i < x.second.size(); i++) {
            if (i < mmcl[x.first].size()) {
                Node->adde(x.second[i], mmcl[x.first][i] + 1, x.first);
            } else {
                Node->adde(x.second[i], MAXN, x.first);
           }
        }
    }
    for (int i = 0; i < n; ++i) {
        pr[i] = i;
    }
    Node->dfs(n);
    for (auto x : anscash) {
        cout << x << '\n';
    }
}

int main() {
    solve();
    return 0;
}

