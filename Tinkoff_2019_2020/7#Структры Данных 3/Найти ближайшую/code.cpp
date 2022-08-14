#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, MAXD = 20;

vector<int> g[MAXN];

unordered_map<int, int> mm[MAXN];

int c[MAXN], sz[MAXN], r[MAXN];

int my_centroid[MAXN][MAXD], dust[MAXN][MAXD];

void dfs_sz(int v, int ranc, int p = -1) {
    sz[v] = 1;
    for (auto x : g[v])
        if (x != p && r[x] > ranc){
            dfs_sz(x, ranc, v);
            sz[v] += sz[x];
        }
}

int dfs_cen(int v, int ranc, int sz_max, int p = -1) {
    for (auto x : g[v])
        if (x != p && r[x] > ranc && sz[x] + sz[x] >= sz_max)
            return dfs_cen(x, ranc, sz_max, v);
    return v;
}

void update(int v, int c, int dis) {
    if (mm[v].find(c) != mm[v].end()) {
        mm[v][c] = min(mm[v][c], dis);
    } else
        mm[v][c] = dis;
}

void prec (int boss, int ranc, int v, int p = -1, int dist = 0) {
    my_centroid[v][ranc] = boss;
    dust[v][ranc] = dist;
    update(boss, c[v], dist);
    for (auto x : g[v])
        if (x != p && r[x] > ranc)
            prec(boss, ranc, x, v, dist + 1);
}

void build(int v = 0, int ranc = 0){
    dfs_sz(v, ranc);
    v = dfs_cen(v, ranc, sz[v]);
    r[v] = ranc;
    prec(v, ranc, v);
    for (auto x : g[v])
        if (r[x] > r[v])
            build(x, ranc + 1);
}

void solve() {
    for (int i = 0; i < MAXN; ++i) {
        r[i] = 30;
        for (int j = 0; j < MAXD; ++j) {
            my_centroid[i][j] = -1;
        }
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        g[x].push_back(i);
        g[i].push_back(x);
    }
    for (int i = 0; i < n; ++i)
        cin >> c[i];
    build();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int v, c;
        cin >> v >> c;
        int ans = MAXN + MAXN;
        for (int i = 0; i < MAXD; ++i)
            if (my_centroid[v][i] != -1 && mm[my_centroid[v][i]].find(c) !=  mm[my_centroid[v][i]].end())
                ans = min(ans, dust[v][i] + mm[my_centroid[v][i]][c]);
        if (ans == MAXN + MAXN)
            cout << -1 << ' ';
        else
            cout << ans << ' ';
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
