#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 500;

vector<long long> g[MAXN];

vector<long long> reb, F, C, first, dust;

bool bfs(long long st, long long fin, long long min_c) {
    for (long long i = 0; i < dust.size(); ++i)
        dust[i] = MAXN + MAXN;
    dust[st] = 0;
    queue<long long> q;
    q.push(st);
    while (!q.empty()) {
        long long v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] >= min_c && dust[reb[x]] == MAXN + MAXN) {
                dust[reb[x]] = dust[v] + 1;
                q.push(reb[x]);
            }
    }
    return dust[fin] != MAXN + MAXN;
}

long long dfs(long long v, long long fin, long long Cmin) {
    if (v == fin)
        return Cmin;
    while (first[v] != g[v].size()) {
        long long id = g[v][first[v]];
        long long to = reb[id];
        if (C[id] - F[id] < Cmin || dust[v] != dust[to] - 1) {
            ++first[v];
            continue;
        }
        long long FF = dfs(to, fin, Cmin);
        if (FF != 0) {
            F[id] += FF;
            F[id ^ 1] -= FF;
            return FF;
        }
        ++first[v];
    }
    return 0;
}

void solve() {
    long long n, m;
    cin >> n >> m;
    long long st = 0, fin = n - 1;
    dust.resize(n);
    reb.resize(m + m);
    F.resize(m + m);
    C.resize(m + m);
    first.resize(n);
    for (long long i = 0; i < m; ++i) {
        long long a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        if (a == b)
            continue;
        g[a].push_back(i + i);
        g[b].push_back(i + i + 1);
        C[i + i] = c;
        C[i + i + 1] = c;
        reb[i + i] = b;
        reb[i + i + 1] = a;
    }
    for (long long Cmin = (1 << 30); Cmin > 0; Cmin>>=1)
        while (bfs(st, fin, Cmin)) {
            while (dfs(st, fin, Cmin));
            for (long long i = 0; i < first.size(); ++i)
                first[i] = 0;
        }
    for (long long i = 0; i < n; ++i)
        dust[i] = 0;
    queue<long long> q;
    dust[st] = 1;
    q.push(st);
    while (!q.empty()) {
        long long v = q.front();
        q.pop();
        for (auto x : g[v])
            if (!dust[reb[x]] && C[x] - F[x] > 0) {
                dust[reb[x]] = 1;
                q.push(reb[x]);
            }
    }
    long long Ce = 0;
    vector<int> ans;
    for (long long i = 0; i < m; ++i) {
        if (dust[reb[i + i]] == 0 && dust[reb[i + i + 1]] == 1) {
            ans.push_back(i);
            Ce += F[i + i];
        }
        else if (dust[reb[i + i]] == 1 && dust[reb[i + i + 1]] == 0) {
            ans.push_back(i);
            Ce += F[i + i + 1];
        }
    }
    cout << ans.size() << ' ' << Ce << '\n';
    for (auto x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
