#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500, MAXM = 10000, INF = 1e9 + 7;

vector<vector<int>> g;
vector<int> dust(MAXN), finishs(MAXM<<1), first(MAXN), C(MAXM<<1), F(MAXM<<1);

bool bfs(int Cmin, int st = 0, int fin = g.size() - 1) {
    for (int i = 0; i < g.size(); ++i)
        dust[i] = INF;
    dust[st] = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (dust[finishs[x]] == INF && C[x] - F[x] >= Cmin) {
                dust[finishs[x]] = dust[v] + 1;
                q.push(finishs[x]);
            }
    }
    return dust[fin] != INF;
}

int dfs(int Cmin, int v = 0, int Cmax = INF, int fin = g.size() - 1) {
    if (v == fin)
        return Cmin;
    while (first[v] != g[v].size()) {
        int id = g[v][first[v]];
        int to = finishs[id];
        if (dust[to] != dust[v] + 1 || C[id] - F[id] < Cmin) {
            ++first[v];
            continue;
        }
        int FF = dfs(Cmin, to, min(Cmax, C[id] - F[id]), fin);
        if (FF == 0) {
            ++first[v];
        } else {
            F[id] += FF;
            F[id ^ 1] -= FF;
            return FF;
        }
    }
    return 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        g[a].push_back(i + i);
        finishs[i + i] = b;
        g[b].push_back(i + i + 1);
        finishs[i + i + 1] = a;
        C[i + i] = c;
    }
    for (int Cmin = 1 << 30; Cmin > 0; Cmin>>=1)
        while (bfs(Cmin)) {
            while (dfs(Cmin));
            for (int i = 0; i < n; ++i)
                first[i] = 0;
        }
    long long ans = 0;
    for (auto x : g[0])
        ans += (long long)F[x];
    cout << ans << '\n';
    return 0;
}
