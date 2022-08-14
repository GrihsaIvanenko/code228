#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20000;

vector<int> g[MAXN];

char used[MAXN];

int tin[MAXN], tup[MAXN], timer = 0;

set<int> ans;

set<pair<int, int>> cash;

void dfs(int v, int p) {
    used[v] = 1;
    tin[v] = tup[v] = timer++;
    int kids = 0;
    for (auto z : g[v]) {
        if (z == p) {
            continue;
        } else if (used[z]) {
            tup[v] = min(tup[v], tin[z]);
        } else {
            dfs(z, v);
            ++kids;
            if (tin[v] <= tup[z] && p != -1) {
                ans.insert(v);
            }
            tup[v] = min(tup[v], tup[z]);
        }
    }
    if (p == -1 && kids > 1) {
        ans.insert(v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b)
            continue;
        if (cash.find({min(a, b), max(a, b)}) != cash.end()) {
            continue;
        }
        cash.insert({min(a, b), max(a, b)});
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < MAXN; ++i) {
        used[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
    cout << endl;
}

int main() {
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    solve();
    return 0;
}
