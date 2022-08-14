#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500, MAXM = 20000;

int F[MAXM], C[MAXM], first[MAXN], fin[MAXM], dust[MAXN];

vector<int> g[MAXN];

int n;

bool bfs(int Cmin, int st = 0, int fish = n - 1) {
    for (int i = 0; i < n; ++i)
        dust[i] = n + 3;
    dust[st] = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v]) {
            if (C[x] - F[x] >= Cmin) {
                int id = fin[x];
                if (dust[id] == n + 3) {
                    q.push(id);
                    dust[id] = dust[v] + 1;
                }
            }
        }
    }
    return dust[fish] != n + 3;
}

int dfs(int Cmin, int v = 0, int fish = n - 1) {
    if (v == fish)
        return Cmin;
    while (first[v] < g[v].size()) {
        int id = g[v][first[v]];
        int to = fin[id];
        if (C[id] - F[id] < Cmin || dust[v] + 1 != dust[to]) {
            ++first[v];
            continue;
        }
        int FF = dfs(Cmin, to, fish);
        if (FF) {
            F[id] += FF;
            F[id ^ 1] -= FF;
            return FF;
        }
        ++first[v];
    }
    return 0;
}

int dfsdfs(vector<int> &way, int v = 0, int fish = n - 1, int Cmin = 1<<30) {
    if (v == fish)
        return Cmin;
    while (first[v] < g[v].size()) {
        int id = g[v][first[v]];
        int to = fin[id];
        if (F[id] <= 0) {
            ++first[v];
            continue;
        }
        int FF = dfsdfs(way, to, fish, min(Cmin, F[id]));
        if (FF == 0) {
            ++first[v];
            continue;
        }
        way.push_back(id);
        return FF;
    }
    return 0;
}

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        fin[i + i + 1] = a;
        fin[i + i] = b;
        F[i + i] = F[i + i + 1] = 0;
        C[i + i] = c;
        C[i + i + 1] = 0;
        g[a].push_back(i + i);
        g[b].push_back(i + i + 1);
    }
    for (int Cmin = 1 << 30; Cmin > 0; Cmin >>= 1)
        while (bfs(Cmin)) {
            for (int i = 0; i < n; ++i)
                first[i] = 0;
            while (dfs(Cmin));
        }
    vector<vector<int>> ways;
    vector<int> ws;
    while (true) {
        ways.push_back({});
        for (int i = 0; i < n; ++i)
            first[i] = 0;
        int Fe = dfsdfs(ways.back());
        if (!Fe) {
            ways.pop_back();
            break;
        }
        ws.push_back(Fe);
        for (auto x : ways.back())
            F[x] -= Fe;
        reverse(ways.back().begin(), ways.back().end());
    }
    cout << ways.size() << '\n';
    for (int i = 0; i < ways.size(); ++i) {
        cout << ws[i] << ' ' << ways[i].size() << ' ';
        for (auto x : ways[i])
            cout << x / 2 + 1 << ' ';
        cout << '\n';
    }
    return;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
