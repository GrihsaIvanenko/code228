#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000, MAXD = 20, INF = 1e9 + 7;

vector<pair<int, unsigned int>> g[MAXN];

vector<int> cens[MAXD];

multiset<unsigned int> hosps[MAXN];

int ranc[MAXN], sz[MAXN], cenup[MAXN][MAXD];
long long dust[MAXN][MAXD];

void dfs(int v, int p = -1, int ran = 0) {
    sz[v] = 1;
    for (auto x : g[v]) {
        if (x.first == p || ranc[x.first] < ran) {
            continue;
        }
        dfs(x.first, v, ran);
        sz[v] += sz[x.first];
    }
}

long long dfs_cen(int v, int r, int max_sz){
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

void dfs_count(int v, int r, unsigned int ds, int anc, int p = -1) {
    cenup[v][r] = anc;
    dust[v][r] = ds;
    for (auto x : g[v]) {
        if (x.first == p || ranc[x.first] < r) {
            continue;
        }
        dfs_count(x.first, r, ds + x.second, anc, v);
    }
}

void build(int v, int r = 0) {
    dfs(v, -1, r);
    int cen = dfs_cen(v, r, sz[v] >> 1);
    cens[r].push_back(cen);
    ranc[cen] = r;
    for (auto x : g[cen]) {
        if (ranc[x.first] > r) {
            build(x.first, r + 1);
        }
    }
}

int main(){
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXD; ++j) {
            cenup[i][j] = -1;
            dust[i][j] = -1;
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        ranc[i] = 27;
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        unsigned int l;
        cin >> a >> b >> l;
        --a;
        --b;
        g[a].push_back({b, l});
        g[b].push_back({a, l});
    }
    build(0, 0);
    for (int i = 0; i < MAXD; ++i) {
        for (auto x : cens[i]) {
            dfs_count(x, i, 0, x);
        }
    }
    for (int i = 0; i < MAXD; ++i) {
        cens[i].clear();
        cens[i].shrink_to_fit();
    }
    for (int i = 0; i < MAXN; ++i) {
        g[i].clear();
        g[i].shrink_to_fit();
    }
    int m;
    cin >> m;
    int tmpp = 0;
    for (int i = MAXD - 1; i >= 0; --i){
        if (cenup[tmpp][i] == -1 || dust[tmpp][i] == -1) {
            continue;
        }
        hosps[cenup[tmpp][i]].insert(dust[tmpp][i]);
    }
    for (int hjjc = 0; hjjc < m; ++hjjc) {
        char type;
        int tmp;
        cin >> type >> tmp;
        --tmp;
        if (type == '?') {
            unsigned int ans = INF;
            for (int i = MAXD - 1; i >= 0; --i) {
                if (cenup[tmp][i] == -1 || dust[tmp][i] == -1 || hosps[cenup[tmp][i]].size() == 0) {
                    continue;
                }
                //cout << *hosps[cenup[tmp][i]].begin() << " " << dust[tmp][i] << endl;
                ans = min(ans, *hosps[cenup[tmp][i]].begin() + (unsigned int)dust[tmp][i]);
            }
            cout << ans << '\n';
        } else if (type == '-') {
            for (int i = MAXD - 1; i >= 0; --i){
                if (cenup[tmp][i] == -1 || dust[tmp][i] == -1) {
                    continue;
                }
                hosps[cenup[tmp][i]].erase(hosps[cenup[tmp][i]].find(dust[tmp][i]));
            }
        } else {
            for (int i = MAXD - 1; i >= 0; --i){
                if (cenup[tmp][i] == -1 || dust[tmp][i] == -1) {
                    continue;
                }
                hosps[cenup[tmp][i]].insert(dust[tmp][i]);
            }
        }
    }
    return 0;
}
