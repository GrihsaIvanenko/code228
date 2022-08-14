#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

vector<int> g[MAXN];

vector<set<int>> cash;

int c[MAXN], id[MAXN], timer = 0;

void dfs(int v) {
    if (g[v].size() == 0) {
        id[v] = timer++;
        set<int> s;
        s.insert(c[v]);
        cash.push_back(s);
        c[v] = 1;
        return;
    }
    int cur = 0;
    for (int i = 0; i < g[v].size(); ++i) {
        dfs(g[v][i]);
        if (c[g[v][cur]] < c[g[v][i]])
            cur = i;
    }
    id[v] = id[g[v][cur]];
    cash[id[v]].insert(c[v]);
    for (int i = 0; i < g[v].size(); ++i) {
        if (i == cur)
            continue;
        for (auto x : cash[id[g[v][i]]])
            cash[id[v]].insert(x);
        cash[id[g[v][i]]].clear();
    }
    g[v].clear();
    g[v].shrink_to_fit();
    c[v] = cash[id[v]].size();
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, roote = 0;
    cin >> n;
    vector<pair<int, int>> verts(n);
    for (int i = 0; i < n; ++i) {
        int p, col;
        cin >> p >> col;
        c[i] = col;
        --p;
        if (p != -1)
            g[p].push_back(i);
        else
            roote = i;
    }
    dfs(roote);
    for (int i = 0; i < n; ++i)
        cout << c[i] << ' ';
    cout << '\n';
    return 0;
}
