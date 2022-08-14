#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150000;

vector<int> g[MAXN];

int st[MAXN], fin[MAXN], cost[MAXN], my[MAXN], dist[MAXN], p[MAXN];

int to(int pos, int v) {
    if (st[pos] == v)
        return fin[pos];
    return st[pos];
}

int get(int x) {
    if (p[x] == x)
        return x;
    return p[x] = get(p[x]);
}

void unite(int a, int b) {
    a = get(a);
    b = get(b);
    p[a] = b;
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, k, S;
    cin >> n >> m >> k >> S;
    for (int i = 0; i < n; ++i) {
        dist[i] = S + 1;
        my[i] = -1;
        p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        g[a].push_back(i);
        g[b].push_back(i);
        st[i] = a;
        fin[i] = b;
        cost[i] = c;
    }
    vector<int> inter(k);
    set<pair<int, int>> s;
    for (int i = 0; i < k; ++i) {
        cin >> inter[i];
        --inter[i];
        my[inter[i]] = inter[i];
        dist[inter[i]] = 0;
        s.insert({dist[inter[i]], inter[i]});
    }
    while (s.size()) {
        pair<int, int> p = *s.begin();
        s.erase(p);
        int v = p.second;
        for (auto x : g[v]) {
            int u = to(x, v);
            if (dist[v] + cost[x] < dist[u]) {
                s.erase({dist[u], u});
                dist[u] = dist[v] + cost[x];
                my[u] = my[v];
                s.insert({dist[u], u});
            }
        }
    }
    for (int i = 0; i < m; ++i)
        if (my[st[i]] != my[fin[i]])
            if ((long long)dist[st[i]] + dist[fin[i]] + (long long)cost[i] <= S)
                unite(my[st[i]], my[fin[i]]);
    for (int i = 0; i < n; ++i)
        dist[i] = S + 1;
    for (auto x : inter)
        if (get(x) == get(0)) {
            s.insert({0, x});
            dist[x] = 0;
        }
    while (s.size()) {
        pair<int, int> p = *s.begin();
        s.erase(p);
        int v = p.second;
        for (auto x : g[v]) {
            int u = to(x, v);
            if (dist[v] + cost[x] < dist[u]) {
                s.erase({dist[u], u});
                dist[u] = dist[v] + cost[x];
                my[u] = my[v];
                s.insert({dist[u], u});
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans += (dist[i] != S + 1);
    cout << ans << '\n';
    for (int i = 0; i < n; ++i)
        if (dist[i] != S + 1)
            cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}
