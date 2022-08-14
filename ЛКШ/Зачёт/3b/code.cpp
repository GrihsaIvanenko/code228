#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, MAXUP = 20;

vector<int> g[MAXN];

int up[MAXN][MAXUP], d[MAXN];

int n;

void dfs(int v, int p, int deep) {
    up[v][0] = p;
    d[v] = deep;
    for (auto x : g[v]) {
        if (x == p) {
           continue;
        }
        dfs(x, v, deep + 1);
    }
}

int lca(int a, int b) {
    if (d[a] < d[b]) {
       swap(a, b);
    }
    for (int i = MAXUP - 1; i >= 0; --i) {
        if (d[a] - d[b] >= (1 << i)) {
            a = up[a][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = MAXUP - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
           a = up[a][i];
           b = up[b][i];
        }
    }
    return up[a][0];
}

void solve() {
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0, 0);
    for (int i = 1; i < MAXUP; ++i) {
        for (int j = 0; j < n; ++j) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
    int root = 0;
    int m;
    cin >> m;
    for (int cher = 0; cher < m; ++cher) {
        char type;
        cin >> type;
        if (type == '!') {
            int t;
            cin >> t;
            root = t - 1;
        } else {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            //cout << lca(a, b) + 1 << '\n';
            cout << (lca(a, b) ^ lca(a, root) ^ lca(b, root)) + 1 << '\n';
        }
    }
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    while (true) {
        cin >> n;
        if (n == 0) {
            return 0;
        }
        solve();
    }
    return 0;
}
