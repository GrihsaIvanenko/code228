#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n;

vector<int> g[MAXN << 1], revg[MAXN << 1], t_s;

char used[MAXN << 1];

int id[MAXN << 1], timer = 0;

void dfs_ts(int v) {
    used[v] = 1;
    for (auto x : g[v]) {
        if (used[x] == 0) {
            dfs_ts(x);
        }
    }
    t_s.push_back(v);
}

void dfs_rev(int v) {
    used[v] = 2;
    id[v] = timer;
    for (auto x : revg[v]) {
        if (used[x] == 1) {
            dfs_rev(x);
        }
    }
}

void solve() {
    t_s.clear();
    for (int i = 0; i < (n << 1); ++i) {
        used[i] = 0;
        g[i].clear();
        revg[i].clear();
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x1, e1, x2, e2;
        cin >> x1 >> e1 >> x2 >> e2;
        g[(x1 << 1) + 1 - e1].push_back((x2 << 1) + e2);
        g[(x2 << 1) + 1 - e2].push_back((x1 << 1) + e1);
        revg[(x2 << 1) + e2].push_back((x1 << 1) + 1 - e1);
        revg[(x1 << 1) + e1].push_back((x2 << 1) + 1 - e2);
    }
    for (int i = 0; i < (n << 1); ++i) {
        if (used[i] == 0) {
            dfs_ts(i);
        }
    }
    /*for (auto x : t_s) {
        cout << x << " ts ";
    }
    cout << endl;
    for (int i = 0; i < (n << 1); ++i) {
        cout << i << " g: ";
        for (auto x : g[i])
            cout << x << " ";
        cout << " revg: ";
        for (auto x : revg[i])
            cout << x << " ";
        cout << endl;
    }*/
    reverse(t_s.begin(), t_s.end());
    for (int i = 0; i < (n << 1); ++i) {
        if (used[t_s[i]] == 1) {
            dfs_rev(t_s[i]);
            ++timer;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (id[i << 1] > id[(i << 1) + 1])
            cout << '0';
        else
            cout << '1';
    }
    cout << '\n';
}

void solver() {
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out", "w", stdout);
    while (cin >> n) {
        solve();
    }
}

int main() {
    solver();
    return 0;
}
