#include <bits/stdc++.h>

using namespace std;

const int MAXUP = 18, MAXN = 100000;

int anc[MAXUP][MAXN], up[MAXUP][MAXN], down[MAXUP][MAXN], d[MAXN];

vector<pair<int, int>> g[MAXN];

void dfs(int v, int p = 0, int deep = 0) {
    d[v] = deep;
    anc[0][v] = p;
    for (auto x : g[v]) {
        if (x.first == p) continue;
        if (x.second) {
            up[0][x.first] = 0;
            down[0][x.first] = 1;
        } else {
            up[0][x.first] = 1;
            down[0][x.first] = 0;
        }
        dfs(x.first, v, deep + 1);
    }
}

void go_up(int &v, int h) {
    for (int i = MAXUP - 1; i >= 0; --i) {
        if ((1 << i) <= h) {
           h -= (1 << i);
           v = anc[i][v];
        }
    }
}

int lca(int a, int b) {
    if (d[a] < d[b]) {
        swap(a, b);
    }
    go_up(a, d[a] - d[b]);
    if (a == b) {
        return a;
    }
    for (int i = MAXUP - 1; i >= 0; --i) {
        if (anc[i][a] != anc[i][b]) {
            a = anc[i][a];
            b = anc[i][b];
        }
    }
    return anc[0][a];
}

bool go(int a, int c, bool upp) {
    if  (d[a] < d[c]) {
        return 0;
    }
    int ans = 1;
    int dh = d[a] - d[c];
    for (int i = MAXUP - 1; i >= 0; --i) {
        if ((1 << i) <= dh) {
            dh -= (1 << i);
           if (upp)ans = min(up[i][a], ans);
           else ans = min(down[i][a], ans);
           a = anc[i][a];
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    up[0][0] = 0;
    down[0][0] = 0;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back({b, 1});
        g[b].push_back({a, 0});
    }
    dfs(0);
    for (int i = 1; i < MAXUP; ++i) {
        for (int v = 0; v < n; ++v) {
            anc[i][v] = anc[i - 1][anc[i - 1][v]];
            up[i][v] = min(up[i - 1][v], up[i - 1][anc[i - 1][v]]);
            down[i][v] = min(down[i - 1][v], down[i - 1][anc[i - 1][v]]);
        }
    }
    int m;
    cin >> m;
    for (int i = 0;i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int c = lca(a, b);
        if (go(a, c, 1) && go(b, c, 0)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
