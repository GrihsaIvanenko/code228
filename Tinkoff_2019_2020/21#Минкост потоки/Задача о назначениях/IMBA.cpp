#include <bits/stdc++.h>

using namespace std;

const int MAXN = 602, MAXM = 302 * 300 * 2;

const long long INF = 1e18;

vector<int> num[MAXN];

int F[MAXM], C[MAXM], P[MAXN], ST[MAXM], FIN[MAXM], timer = 0;

long long COST[MAXM];

vector<long long> fi, dust;

void push_reb(int v, int to, int c, int cost) {
    num[v].push_back(timer);
    ST[timer] = v;
    FIN[timer] = to;
    F[timer] = 0;
    C[timer] = c;
    COST[timer++] = cost;
}

void add_reb(int v, int u, int c, int cost) {
    push_reb(v, u, c, cost);
    push_reb(u, v, 0, -cost);
}

bitset<MAXN> in_q, used;

int main() {
    used.reset();
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> v[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            add_reb(i, n + j, 1, v[i][j]);
        add_reb(n + n, i, 1, 0);
        add_reb(i + n, n + n + 1, 1, 0);
    }
    n = n + n + 2;
    fi.resize(n), dust.resize(n);
    int st = n - 2, fin = n - 1;
    while (true) {
        used.reset();
        for (int i = 0; i < n; ++i)
            dust[i] = INF;
        dust[st] = 0;
        int cur;
        for (int iter = 0; iter < n; ++iter) {
            cur = -1;
            for (int i = 0; i < n; ++i)
                if (dust[i] != INF && !used[i])
                    if (cur == -1 || dust[cur] > dust[i])
                        cur = i;
            if (cur == -1)
                break;
            used[cur] = 1;
            for (auto x : num[cur])
                if (C[x] - F[x] && !used[FIN[x]] && dust[FIN[x]] > dust[cur] + fi[cur] - fi[FIN[x]] + COST[x]) {
                    dust[FIN[x]] = dust[cur] + fi[cur] - fi[FIN[x]] + COST[x];
                    P[FIN[x]] = x;
                }
        }
        if (dust[fin] == INF)
            break;
        for (int i = 0; i < n; ++i)
            dust[i] += fi[i];
        swap(dust, fi);
        vector<int> way;
        int v = fin;
        while (v != st) {
            way.push_back(P[v]);
            v = ST[way.back()];
        }
        for (auto x : way) {
            ++F[x];
            --F[x ^ 1];
        }
    }
    n = n - 1>>1;
    long long ans = 0;
    vector<pair<int, int>> answ(n);
    for (int i = 0; i < n; ++i)
        for (auto x : num[i])
        if (F[x] > 0) {
            answ[i] = {i + 1, FIN[x] - n + 1};
            ans += COST[x];
        }
    cout << ans << '\n';
    for (auto x : answ)
        cout << x.first << ' ' << x.second << '\n';
}
