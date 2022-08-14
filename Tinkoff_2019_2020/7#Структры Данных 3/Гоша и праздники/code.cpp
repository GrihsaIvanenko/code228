#include <bits/stdc++.h>

using namespace std;

const int MAXN = 262144, MAXD = 20;

vector<pair<int, long long>> g[MAXN];

int sz[MAXN], r[MAXN];

int C[MAXN][MAXD];

long long D[MAXN][MAXD];

void dfs_sz(int v, int ranc, int p = -1) {
    sz[v] = 1;
    for (auto x : g[v])
        if (x.first != p && r[x.first] > ranc){
            dfs_sz(x.first, ranc, v);
            sz[v] += sz[x.first];
        }
}

int dfs_cen(int v, int ranc, int sz_max, int p = -1) {
    for (auto x : g[v])
        if (x.first != p && r[x.first] > ranc && sz[x.first] + sz[x.first] >= sz_max)
            return dfs_cen(x.first, ranc, sz_max, v);
    return v;
}

void prec(int v, int ranc, int boss, long long dust = 0, int p = -1) {
    C[v][ranc] = boss;
    D[v][ranc] = dust;
    for (auto x : g[v])
        if (x.first != p && r[x.first] > ranc)
            prec(x.first, ranc, boss, dust + x.second, v);
}

void build(int v = 0, int ranc = 0) {
    dfs_sz(v, ranc);
    v = dfs_cen(v, ranc, sz[v]);
    r[v] = ranc;
    prec(v, r[v], v);
    for (auto x : g[v])
        if (r[x.first] > ranc)
            build(x.first, ranc + 1);
}

void solve() {
    for (int i = 0; i < MAXN; ++i) {
        r[i] = 30;
        for (int j = 0; j < MAXD; ++j)
            C[i][j] = -1;
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        --a;
        --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    build();
    int m;
    cin >> m;
    vector<pair<pair<long long, int>, pair<int, int>>> mail_ru;
    unordered_map<int, int> cash;
    int timer = 1;
    for (int i = 0; i < m; ++i) {
        int c;
        long long d;
        cin >> c >> d;
        --c;
        mail_ru.push_back({{d, 0}, {c, c}});
        for (int j = 0; j < MAXD; ++j)
            if (C[c][j] != -1) {
                mail_ru.push_back({{d - D[c][j], timer}, {C[c][j], c}});
                mail_ru.push_back({{d, -(timer++)}, {C[c][j], c}});
                mail_ru.push_back({{d, timer}, {c, C[c][j]}});
                mail_ru.push_back({{d + D[c][j], -(timer++)}, {c, C[c][j]}});
            }
    }
    sort(mail_ru.begin(), mail_ru.end());
    vector<int> now(n);
    int ans = 0;
    for (auto x : mail_ru) {
        if (x.first.second == 0) {
            ans = max(ans, ++now[x.second.second]);
        } else if (x.first.second > 0) {
            int id = x.first.second - 1;
            cash[id] = now[x.second.first];
        } else {
            int id = -x.first.second - 1;
            now[x.second.second] = max(now[x.second.second], cash[id]);
        }
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
