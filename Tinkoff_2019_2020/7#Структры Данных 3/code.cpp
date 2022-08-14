#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001, MAXUP = 20;

int ranc[MAXN];

int cenup[MAXUP][MAXN];

vector<int> g[MAXN];

vector<int> sz(MAXN);

vector<int> good_id(MAXN);

vector<vector<int>> centroids(MAXUP);

void dfs_calc(int v, int r, int p = -1) {
    sz[v] = 1;
    int good = -1, i = 0;
    for (auto x : g[v]) {
        ++i;
        if (x == p || ranc[x] < r)
            continue;
        dfs_calc(x, r, v);
        if (good == -1 || sz[g[v][good]] < sz[x])
            good = i - 1;
        sz[v] += sz[x];
    }
    good_id[v] = good;
}

int dfs_find_centroid(int v, int r, int k) {
    if (good_id[v] == -1 || sz[g[v][good_id[v]]] * 2 < k) {
        return v;
    }
    return dfs_find_centroid(g[v][good_id[v]], r, k);
}

void build_centroid_decompozition(int v = 0, int r = 0) {
    dfs_calc(v, r);
    int new_centroid = dfs_find_centroid(v, r, sz[v]);
    ranc[new_centroid] = r;
    centroids[r].push_back(new_centroid);
    for (auto x : g[new_centroid])
        if (ranc[x] > r)
            build_centroid_decompozition(x, r + 1);
}

void dfs_counter(int v, int r, int good, int p = -1) {
    cenup[r][v] = good;
    for (auto x : g[v]) {
        if (ranc[x] < r || x == p)
            continue;
        dfs_counter(x, r, good, v);
    }
}

void calc() {
    for (int i = 0; i < MAXUP; ++i){
        for (auto x : centroids[i])
            dfs_counter(x, i, x);
        centroids[i].clear();
        centroids[i].shrink_to_fit();
    }
    centroids.clear();
    centroids.shrink_to_fit();
}

int ans = 0;

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN; ++i) {
        ranc[i] = MAXUP;
    }
    for (int i = 0; i < MAXUP; ++i)
        for (int j = 0; j < MAXN; ++j)
            cenup[i][j] = -1;
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
    build_centroid_decompozition();
    sz.clear();
    sz.shrink_to_fit();
    good_id.clear();
    good_id.shrink_to_fit();
    calc();
    for (int i = 0; i < n; ++i)
        if (ranc[i] == 0)
            cout << "0 ";
        else
            cout << cenup[ranc[i] - 1][i] + 1 << " ";
    cout << '\n';
    return 0;
}
