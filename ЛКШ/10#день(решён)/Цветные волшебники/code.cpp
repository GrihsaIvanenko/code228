#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, MAXM = 500000, MAXP = 20;

vector<pair<int, int>> g[MAXN], rebs;

vector<int> newg[MAXN];

int tin[MAXN], fup[MAXN], used[MAXN], col[MAXN], timer = 0, anc[MAXN][MAXP], h[MAXN];

int bridge[MAXN];

void dfs_counter(int v, int p, int deep = 0) {
    h[v] = deep;
    anc[v][0] = p;
    for (auto x : newg[v])
        if (x != p)
            dfs_counter(x, v, deep + 1);
}

void dfs(int v, int p = -1) {
    tin[v] = fup[v] = timer++;
    used[v] = 1;
    for (auto x : g[v]) {
        if (x.first == p)
            continue;
        if (!used[x.first]) {
            dfs(x.first, v);
            if (fup[x.first] > tin[v])
                bridge[x.second] = 1;
            fup[v] = min(fup[v], fup[x.first]);
        } else {
            fup[v] = min(fup[v], tin[x.first]);
        }
    }
}

void dfs_color(int v) {
    col[v] = timer;
    used[v] = 2;
    for (auto x : g[v]) {
        if (used[x.first] != 2 && bridge[x.second] != 1)
            dfs_color(x.first);
    }
}

int lca(int a, int b) {
    if (h[a] < h[b])
        swap(a, b);
    for (int i = MAXP - 1; i >= 0; --i)
        if (h[a] - h[b] >= (1 << i))
            a = anc[a][i];
    if (a == b)
        return a;
    for (int i = MAXP - 1; i >= 0; --i)
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    return anc[a][0];
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    rebs.resize(m);
    for (int i = 0; i < n; ++i)
        used[i] = 0;
    --k;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        rebs[i] = {a, b};
        bridge[i] = 0;
    }
    dfs(0);
    timer = 0;
    for (int i = 0; i < n; ++i)
        if (used[i] == 1) {
            dfs_color(i);
            ++timer;
        }
    for (int i = 0; i < m; ++i) {
        if (bridge[i]) {
            int a = rebs[i].first, b = rebs[i].second;
            a = col[a], b = col[b];
            newg[a].push_back(b);
            newg[b].push_back(a);
        }
    }
    k = col[k];
    dfs_counter(k, k);
    for (int j = 1; j < MAXP; ++j)
        for (int i = 0; i < n; ++i)
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a = col[a - 1];
        b = col[b - 1];
        cout << h[lca(a, b)] << '\n';
    }
    return 0;
}
