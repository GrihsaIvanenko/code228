#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, MAXD = 20, INF = 1e9 + 101;

vector<pair<int, int>> g[MAXN];

vector<int> cen[MAXD];
vector<pair<int, pair<int, int>>> cash[MAXN];

int r[MAXN], sz[MAXN], cenup[MAXN][MAXD], d[MAXN][MAXD];

void count_sz(int v, int rr, int p = -1) {
    sz[v] = 1;
    for (auto x : g[v]) {
        if (x.first != p && r[x.first] > rr) {
            count_sz(x.first, rr, v);
            sz[v] += sz[x.first];
        }
    }
}

int search_cen(int v, int p, int rr, int max_sz) {
    for (auto x : g[v])
        if (x.first != p && r[x.first] > rr && sz[x.first] + sz[x.first] >= max_sz)
            return search_cen(x.first, v, rr, max_sz);
    return v;
}

void build(int v, int rr) {
    count_sz(v, rr, -1);
    v = search_cen(v, -1, rr, sz[v]);
    r[v] = rr;
    cen[rr].push_back(v);
    for (auto x : g[v]) {
        if (r[x.first] > rr)
            build(x.first, rr + 1);
    }
}

void dfs(int v, int rr, int p, int good, int dust) {
    cenup[v][rr] = good;
    d[v][rr] = dust;
    for (auto x : g[v])
        if (x.first != p && r[x.first] > rr)
            dfs (x.first, rr, v, good, dust + x.second);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        r[i] = MAXD;
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    build(0, 0);
    for (int i = 0; i < MAXD; ++i)
        for (auto v : cen[i])
            dfs(v, i, -1, v, 0);
    for (int i = 0; i < n; ++i) {
        cash[i].push_back({INF, {-1, 0}});
    }
    int q;
    cin >> q;
    for (int cnt = 0; cnt < q; ++cnt) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, dd, c;
            cin >> v >> dd >> c;
            --v;
            for (int rr = r[v]; rr >= 0; --rr) {
                int my_sen = cenup[v][rr], dust = d[v][rr];
                while (cash[my_sen].back().first <= dd - dust)
                    cash[my_sen].pop_back();
                if (dd - dust >= 0)
                    cash[my_sen].push_back({dd - dust, {cnt, c}});
            }
        } else {
            int v;
            cin >> v;
            --v;
            pair<int, int> cur_ans = {-1, 0};
            for (int rr = r[v]; rr >= 0; --rr) {
                int my_cen = cenup[v][rr], dust = d[v][rr];
                int lb = 0, rb = cash[my_cen].size();
                while (rb - lb > 1) {
                    int mid = (lb + rb) >> 1;
                    if (cash[my_cen][mid].first >= dust)
                        lb = mid;
                    else
                        rb = mid;
                }
                if (cash[my_cen][lb].second.first > cur_ans.first) {
                    cur_ans = cash[my_cen][lb].second;
                }
            }
            cout << cur_ans.second << '\n';
        }
    }
    return 0;
}

