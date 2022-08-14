#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000, MAXUP = 20, INF = 1e9 + 7;

vector<int> g[MAXN];

int up[MAXN][MAXUP], cost[MAXN][MAXUP], d[MAXN];

void dfs(int v, int deep = 0) {
    d[v] = deep;
    for (auto x : g[v]) {
        dfs(x, deep + 1);
    }
}

pair<int, int> upp(int v, int d) {
    int ans = INF;
    for (int i = MAXUP - 1; i >= 0; --i) {
        if ((1 << i) <= d) {
            d -= (1 << i);
            ans = min(ans, cost[v][i]);
            v = up[v][i];
        }
    }
    return {v, ans};
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < MAXUP; ++i) {
        up[0][i] = 0;
        cost[0][i] = INF;
    }
    for (int i = 1; i < n; ++i) {
        int v, coste;
        cin >> v >> coste;
        --v;
        g[v].push_back(i);
        up[i][0] = v;
        cost[i][0] = coste;
    }
    dfs(0);
    for (int i = 1; i < MAXUP; ++i) {
        for (int j = 1; j < n; ++j) {
            up[j][i] = up[up[j][i - 1]][i - 1];
            cost[j][i] = min(cost[j][i - 1], cost[up[j][i - 1]][i - 1]);
        }
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (d[a] < d[b]) {
            swap(a, b);
        }
        pair<int, int> p = upp(a, d[a] - d[b]);
        a = p.first;
        int ans = p.second;
        if (a == b) {
            cout << ans << '\n';
            continue;
        }
        for (int i = MAXUP - 1; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                ans = min(ans, cost[a][i]);
                ans = min(ans, cost[b][i]);
                a = up[a][i];
                b = up[b][i];
            }
        }
        ans = min(ans, cost[a][0]);
        ans = min(ans, cost[b][0]);
        cout << ans << '\n';
    }
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    solve();
    return 0;
}

