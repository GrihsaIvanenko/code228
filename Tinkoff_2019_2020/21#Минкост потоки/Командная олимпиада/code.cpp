#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202, MAXM = 100 * 100 * 2 + 400, INF = 1e9 + 7;

vector<int> num[MAXN];

int sts[MAXM], fins[MAXM], F[MAXM], C[MAXM], COST[MAXM], dust[MAXN], p[MAXN], n, m, timer = 0;

void push_reb(int v, int u, int f, int c) {
    num[v].push_back(timer);
    sts[timer] = v;
    fins[timer] = u;
    F[timer] = 0;
    C[timer] = f;
    COST[timer] = c;
}

void add_edge(int v, int u, int f, int c) {
    push_reb(v, u, f, c);
    ++timer;
    push_reb(u, v, 0, -c);
    ++timer;
}

void solve() {
    cin >> n;
    vector<vector<int>> v(n);
    for (int i = 0; i < n + n; ++i) {
        int x;
        cin >> x;
        v[x - 1].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int p1 = j, p2 = j + n;
            int dust = abs(v[i][0] - p1) + abs(v[i][1] - p2);
            add_edge(i, n + j, 1, dust);
        }
        add_edge(n + n, i, 1, 0);
        add_edge(i + n, n + n + 1, 1, 0);
    }
    n = n + n + 2;
    set<int> q;
    while (true) {
        for (int i = 0; i < n; ++i)
            dust[i] = INF;
        dust[n - 2] = 0;
        q.insert(n - 2);
        while (!q.empty()) {
            int v = *q.begin();
            q.erase(v);
            for (auto x : num[v]) {
                if (C[x] - F[x] > 0 && dust[fins[x]] > dust[v] + COST[x]) {
                    dust[fins[x]] = dust[v] + COST[x];
                    p[fins[x]] = x;
                    q.insert(fins[x]);
                }
            }
        }
        if (dust[n - 1] == INF)
            break;
        vector<int> way;
        int v = n - 1;
        while (v != n - 2) {
            way.push_back(p[v]);
            v = sts[way.back()];
        }
        for (auto x : way) {
            ++F[x];
            --F[x ^ 1];
        }
    }
    n = (n - 1) / 2;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
       for (auto x : num[i]) {
            if (F[x] == 1) {
                ans[fins[x] - n] = i + 1;
            }
        }
    for (auto x : ans) cout << x << ' ';
    for (auto x : ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    //freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
