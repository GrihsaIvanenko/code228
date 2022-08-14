#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

vector<int> fins, F, C, COST, fi, sts, p, dust;

void solve() {
    int n, m;
    cin >> n >> m;
    fins.resize(m + m);
    F.resize(m + m);
    C.resize(m + m);
    sts.resize(m + m);
    COST.resize(m + m);
    fi.resize(n);
    p.resize(n);
    dust.resize(n);
    vector<vector<int>> num(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a;
        --b;
        num[a].push_back(i + i);
        num[b].push_back(i + i + 1);
        fins[i + i] = b;
        fins[i + i + 1] = a;
        sts[i + i] = a;
        sts[i + i + 1] = b;
        C[i + i] = c;
        COST[i + i] = d;
        COST[i + i + 1] = -d;
    }
    long long ans = 0;
    int st = 0, fin = n - 1;
    for (int i = 0; i < n; ++i)
        fi[i] = INF;
    fi[st] = 0;
    for (int iter = 0; iter < n; ++iter)
        for (int i = 0; i < m + m; ++i)
            if (fi[sts[i]] + COST[i] < fi[fins[i]])
                fi[fins[i]] = min(fi[fins[i]], fi[sts[i]] + COST[i]);
    while (true) {
        for (int i = 0; i < n; ++i)
            dust[i] = INF;
        dust[st] = 0;
        p[st] = st;
        set<pair<int, int>> s;
        s.insert({dust[st], st});
        while (!s.empty()) {
            int dis = (*s.begin()).first, v = (*s.begin()).second;
            s.erase({dis, v});
            for (auto x : num[v])
                if (C[x] - F[x] > 0 && dust[fins[x]] > dust[v] + COST[x] + fi[sts[x]] - fi[fins[x]]) {
                    p[fins[x]] = x;
                    s.erase({dust[fins[x]], fins[x]});
                    dust[fins[x]] = dust[v] + COST[x] + fi[sts[x]] - fi[fins[x]];
                    s.insert({dust[fins[x]], fins[x]});
                }
        }
        if (dust[fin] == INF)
            break;
        vector<int> way;
        int v = fin;
        while (v != st) {
            way.push_back(p[v]);
            v = sts[p[v]];
        }
        int cur = C[way[0]] - F[way[0]];
        for (int i = 1; i < way.size(); ++i)
            cur = min(cur, C[way[i]] - F[way[i]]);
        for (auto x : way) {
            F[x] += cur;
            F[x ^ 1] -= cur;
            ans += (long long)cur * (long long)(COST[x]);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
