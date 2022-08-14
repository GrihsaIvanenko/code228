#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 100000, MAXD = 24, INF = 1e10;
vector<pair<long long, long long>> g[MAXN];

vector<long long> cens[MAXD];

vector<pair<long long, pair<long long, long long>>> changes[MAXN];

long long ranc[MAXN], sz[MAXN], cenup[MAXN][MAXD], dust[MAXN][MAXD];

void dfs(long long v, long long p = -1, long long ran = 0) {
    sz[v] = 1;
    for (auto x : g[v]) {
        if (x.first == p || ranc[x.first] < ran) {
            continue;
        }
        dfs(x.first, v, ran);
        sz[v] += sz[x.first];
    }
}

long long dfs_cen(long long v, long long r, long long max_sz){
    for (auto x : g[v]) {
        if (ranc[x.first] < r || sz[x.first] > sz[v]) {
            continue;
        }
        if (sz[x.first] > max_sz) {
           return dfs_cen(x.first, r, max_sz);
        }
    }
    return v;
}

void dfs_count(long long v, long long r, long long ds, long long anc, long long p = -1) {
    cenup[v][r] = anc;
    dust[v][r] = ds;
    for (auto x : g[v]) {
        if (x.first == p || ranc[x.first] < r) {
            continue;
        }
        dfs_count(x.first, r, ds + x.second, anc, v);
    }
}

void build(long long v, long long r = 0) {
    dfs(v, -1, r);
    long long cen = dfs_cen(v, r, sz[v] >> 1);
    cens[r].push_back(cen);
    ranc[cen] = r;
    for (auto x : g[cen]) {
        if (ranc[x.first] > r) {
            build(x.first, r + 1);
        }
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    for (long long i = 0; i < MAXN; ++i) {
        for (long long j = 0; j < MAXD; ++j) {
            cenup[i][j] = -1;
            dust[i][j] = -1;
        }
        changes[i].push_back({INF, {-1, 0}});
    }
    for (long long i = 0; i < MAXN; ++i) {
        ranc[i] = 25;
    }
    long long n;
    cin >> n;
    for (long long i = 1; i < n; ++i) {
        long long a, b;
        long long l;
        cin >> a >> b >> l;
        --a;
        --b;
        g[a].push_back({b, l});
        g[b].push_back({a, l});
    }
    build(0, 0);
    for (long long i = 0; i < MAXD; ++i) {
        for (auto x : cens[i]) {
            dfs_count(x, i, 0, x);
        }
    }
    for (long long i = 0; i < MAXD; ++i) {
        cens[i].clear();
        cens[i].shrink_to_fit();
    }
    for (long long i = 0; i < MAXN; ++i) {
        g[i].clear();
        g[i].shrink_to_fit();
    }
    long long m;
    cin >> m;
    for (long long i = 0; i < m; ++i) {
        long long type;
        cin >> type;
        if (type == 1) {
            long long v, d, c;
            cin >> v >> d >> c;
            --v;
            for (long long j = MAXD - 1; j > -1; --j) {
                if (cenup[v][j] == -1 || dust[v][j] == -1 || dust[v][j] > d) {
                    continue;
                }
                while (changes[cenup[v][j]].back().first <= d - dust[v][j]) {
                    changes[cenup[v][j]].pop_back();
                }
                changes[cenup[v][j]].push_back({d - dust[v][j], {i, c}});
            }
        } else {
            long long v;
            cin >> v;
            --v;
            pair<long long, long long> cur = {-2, 0};
            for (long long j = MAXD - 1; j > -1; --j) {
                if (cenup[v][j] == -1 || dust[v][j] == -1) {
                    continue;
                }
                long long lb = 0, rb = changes[cenup[v][j]].size();
                while (rb - lb > 1) {
                    long long mid = (lb + rb) >> 1;
                    if (changes[cenup[v][j]][mid].first >= dust[v][j]) {
                        lb = mid;
                    } else {
                        rb = mid;
                    }
                }
                if (changes[cenup[v][j]][lb].second.first >= cur.first) {
                    cur = changes[cenup[v][j]][lb].second;
                }
            }
            cout << cur.second << '\n';
        }
    }
    return 0;
}
