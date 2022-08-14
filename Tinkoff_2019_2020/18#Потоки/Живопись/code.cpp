#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4902, INF = 1e9 + 7;

int timer = 0, ST, FIN, n, m;

vector<int> g[MAXN], st, fin, fir, C, F, dust;

int pos(pair<int, int> p) {
    return p.first * m + p.second;
}

bool sosed(pair<int, int> a, pair<int, int> b) {
    return (abs(a.first - b.first) + abs(a.second - b.second) == 1);
}

void add(int a, int b, int c) {
    g[a].push_back(timer);
    st.push_back(a);
    fin.push_back(b);
    C.push_back(c);
    F.push_back(0);
    ++timer;
}

void add_reb(int a, int b, int c) {
    if (c == 0)
        return;
    add(a, b, c);
    add(b, a, 0);
}

void add_reb_(int a, int b, int c) {
    if (c == 0)
        return;
    add(a, b, c);
    add(b, a, c);
}

bool bfs(int s, int f, int c) {
    for (int i = 0; i < MAXN; ++i)
        dust[i] = INF;
    dust[s] = 0;
    queue<int> q;
    q.push(s);
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] >= c && dust[fin[x]] == INF) {
                dust[fin[x]] = dust[v] + 1;
                q.push(fin[x]);
            }
    }
    return !(dust[f] == INF);
}

int dfs(int v, int toto, int Cmax) {
    if (v == toto)
        return Cmax;
    while (fir[v] != g[v].size()) {
        int id = g[v][fir[v]];
        if (C[id] - F[id] < Cmax) {
            ++fir[v];
            continue;
        }
        int to = fin[id];
        if (dust[v] != dust[to] - 1) {
            ++fir[v];
            continue;
        }
        int FF = dfs(to, toto, Cmax);
        if (FF) {
            F[id] += FF;
            F[id ^ 1] -= FF;
            return Cmax;
        }
        ++fir[v];
    }
    return 0;
}

int main() {
    int we, be, ge;
    cin >> n >> m >> we >> be >> ge;
    ST = n * m, FIN = n * m + 1;
    vector<pair<int, int>> ww, bb;
    string ccc;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            char x;
            cin >> x;
            ccc.push_back(x);
            if (x == 'W')
                ww.push_back({i, j});
            else
                bb.push_back({i, j});
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < n; ++k)
                for (int l = 0; l < m; ++l)
                    if(sosed({i, j}, {k, l}))
                        add_reb(pos({i, j}), pos({k, l}), ge);
    for (auto x : ww)
        add_reb(ST, pos(x), be);
    for (auto x : bb)
        add_reb(pos(x), FIN, we);
    dust.resize(MAXN);
    fir.resize(MAXN);
    for (int Cmax = 512; Cmax; Cmax >>= 1)
        while (bfs(ST, FIN, Cmax)) {
            for (int i = 0; i < fir.size(); ++i)
                fir[i] = 0;
            while (dfs(ST, FIN, Cmax));
        }
    int ans = 0;
    for (auto x : g[ST])
        ans += F[x];
    cout << ans << '\n';
    return 0;
}
