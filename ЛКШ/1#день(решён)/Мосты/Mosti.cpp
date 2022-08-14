#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int MAXN = 20000;

vector<pair<int, int>> g[MAXN];

char used[MAXN];

int tin[MAXN], tup[MAXN], timer = 0;

vector<int> ans;

void dfs(int v, int p) {
    used[v] = 1;
    tin[v] = tup[v] = timer++;
    for (auto z : g[v]) {
        if (z.x == p) {
            continue;
        } else if (used[z.x]) {
            tup[v] = min(tup[v], tin[z.x]);
        } else {
            dfs(z.x, v);
            if (tin[v] < tup[z.x]) {
                ans.push_back(z.y);
            }
            tup[v] = min(tup[v], tup[z.x]);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    for (int i = 0; i < MAXN; ++i) {
        used[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
    cout << endl;
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    solve();
    return 0;
}
