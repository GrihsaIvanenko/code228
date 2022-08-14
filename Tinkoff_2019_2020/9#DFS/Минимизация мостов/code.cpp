#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001, INF = 1e9 + 7;

vector<int> g[MAXN];

set<pair<int, int>> ban;

int used[MAXN], tin[MAXN], fup[MAXN], dust[MAXN], timer = 0, ans = 0, del = 0;

pair<int, int> get_reb(int a, int b) {
    return {min(a, b), max(a, b)};
}

void dfs_search_bridges(int v, set<pair<int, int>> &s, int p = -1) {
    used[v] = 1;
    tin[v] = fup[v] = timer++;
    for (auto x : g[v]) {
        if (x == p)
            continue;
        if (used[x] == 0) {
            dfs_search_bridges(x, s, v);
            fup[v] = min(fup[v], fup[x]);
            if (fup[x] > tin[v] && ban.find(get_reb(x, v)) == ban.end())
                s.insert(get_reb(x, v));
        } else {
            fup[v] = min(fup[v], tin[x]);
        }
    }
}

void work(int v) {
    set<pair<int, int>> bridges;
    dfs_search_bridges(v, bridges);
    ans += bridges.size();
    deque<int> d;
    vector<int> visited;
    d.push_back(v);
    while (!d.empty()) {
        int x = d.front();
        d.pop_front();
        if (used[x] == 2)
            continue;
        used[x] = 2;
        visited.push_back(x);
        for (int i = 0; i < g[x].size(); ++i) {
            if (used[g[x][i]] == 2)
                continue;
            if (bridges.find(get_reb(x, g[x][i])) != bridges.end()) {
                d.push_back(g[x][i]);
                dust[g[x][i]] = dust[x] + 1;
            } else {
                d.push_front(g[x][i]);
                dust[g[x][i]] = dust[x];
            }
        }
    }
    int cur = v;
    for (auto x : visited)
        if (dust[x] > dust[cur])
            cur = x;
    for (auto x : visited)
        dust[x] = 0;
    d.push_back(cur);
    while (!d.empty()) {
        int x = d.front();
        d.pop_front();
        if (used[x] == 3)
            continue;
        used[x] = 3;
        for (int i = 0; i < g[x].size(); ++i) {
            if (used[g[x][i]] == 3)
                continue;
            if (bridges.find(get_reb(x, g[x][i])) != bridges.end()) {
                d.push_back(g[x][i]);
                dust[g[x][i]] = dust[x] + 1;
            } else {
                d.push_front(g[x][i]);
                dust[g[x][i]] = dust[x];
            }
        }
    }
    int cur_ans = cur;
    for (auto x : visited)
        if (dust[cur_ans] < dust[x])
            cur_ans = x;
    del = max(del, dust[cur_ans]);
    for (auto x : visited) {
        dust[x] = 0;
    }
    visited.clear();
    visited.shrink_to_fit();
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN; ++i)
        dust[i] = 0;
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> s;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b)
            continue;
        --a;
        --b;
        if (s.find(get_reb(a, b)) != s.end())
            ban.insert(get_reb(a, b));
        s.insert(get_reb(a, b));
    }
    for (auto x : s) {
        g[x.first].push_back(x.second);
        g[x.second].push_back(x.first);
    }
    s.clear();
    for (int i = 0; i < n; ++i)
        used[i] = 0;
    for (int i = 0; i < n; ++i)
        if (used[i] == 0)
            work(i);
    cout << ans - del << endl;
    return 0;
}
