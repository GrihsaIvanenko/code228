#include <bits/stdc++.h>

using namespace std;

const int MAXN =  500000;

vector<int> g[MAXN];

int dust[MAXN], dusmax[MAXN];

void dfs_duster(int v, int d = 0, int p = -1) {
    dust[v] = d;
    for (auto x : g[v])
        if (x != p)
            dfs_duster(x, d + 1, v);
}

int solve_diameter(int m) {
    dfs_duster(0);
    int good = 0;
    for (int i = 1; i < m; ++i)
        if (dust[good] < dust[i])
            good = i;
    dfs_duster(good);
    int dmax = 0;
    for (int i = 0; i < m; ++i)
        if (dust[i] > dmax)
            dmax = dust[i];
    return dmax;
}

void dfs_dumpster(int v, int d = 0, int p = -1) {
    dust[v] = d;
    dusmax[v] = 0;
    for (auto x : g[v])
        if (x != p) {
            dfs_dumpster(x, d + 1, v);
            dusmax[v] = max(dusmax[v], dusmax[x] + 1);
        }
}

int dfs_govnomes(int v, int p = -1) {
    int gv = -1;
    for (auto x : g[v]) {
        if (x != p && (gv == -1 || dusmax[gv] < dusmax[x]) && (p == -1 || dusmax[x] > dusmax[p] + 1))
            gv = x;
    }
    if (gv == -1) {
        return max(dusmax[v], dusmax[p] + 1);
    }
    dusmax[v] = 0;
    for (auto x : g[v]) {
        if (x != gv)
            dusmax[v] = max(dusmax[v], dusmax[x] + 1);
    }
    return dfs_govnomes(gv, v);
}

int solve (int n) {
    dfs_duster(0);
    int v = 0;
    for (int i = 1; i < n; ++i)
        if (dust[v] < dust[i])
            v = i;
    dfs_dumpster(v);
    return dfs_govnomes(v);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int K = solve(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        g[i].clear();
    }
    for (int i = 1; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int V = solve_diameter(m);
    //cout << K << " " << V << endl;
    if (K > V)
        cout << "GGEZ\n";
    else
        cout << "FF\n";
    return 0;
}

