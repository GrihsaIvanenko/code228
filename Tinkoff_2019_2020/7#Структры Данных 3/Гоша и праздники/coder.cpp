#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000, MAXD = 20;

vector<pair<int, long long>> g[MAXN];

int h[MAXN];

long long dust[MAXN];

int anc[MAXN][MAXD];

void dfs_calc(int v = 0, long long d = 0, int p = 0, int deep = 0) {
    anc[v][0] = p;
    h[v] = deep;
    dust[v] = d;
    for (auto x : g[v]) {
        if (x.first != p)
            dfs_calc(x.first, d + x.second, v, deep + 1);
    }
}

int lca(int a, int b) {
    if (h[a] < h[b])
        swap(a, b);
    for (int i = MAXD - 1; i >= 0; --i)
        if (h[a] - h[b] >= (1 << i))
            a = anc[a][i];
    if (a == b)
        return a;
    for (int i = MAXD - 1; i >= 0; --i)
        if (anc[a][i] != anc[b][i]){
            a = anc[a][i];
            b = anc[b][i];
        }
    return anc[a][0];
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        long long c;
        cin >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs_calc();
    for (int i = 1; i < MAXD; ++i)
        for (int j = 0; j < n; ++j)
            anc[j][i] = anc[anc[j][i - 1]][i - 1];
    int m;
    cin >> m;
    vector<pair<long long, int>> events(m);
    for (int i = 0; i < m; ++i) {
        int c, d;
        cin >> c >> d;
        events[i] = {d, c - 1};
    }
    sort(events.begin(), events.end());
    int ans = 0;
    vector<int> could(m, 1);
    for (int i = 0; i < m; ++i) {
        int a = events[i].second;
        for (int j = 0; j < i; ++j) {
            int b = events[j].second;
            int c = lca(a, b);
            if (events[j].first + dust[a] + dust[b] - dust[c] - dust[c] <= events[i].first) {
                could[i] = max(could[i], could[j] + 1);
            }
        }
        ans = max(ans, could[i]);
    }
    cout << ans << '\n';
}
