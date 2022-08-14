#include <bits/stdc++.h>

using namespace std;

vector<int> C, F, st, fin, first, dust;

vector<vector<int>> g;

int timer = 2;

void add(int a, int b, int c) {
    g[a].push_back(C.size());
    C.push_back(c);
    F.push_back(0);
    st.push_back(a);
    fin.push_back(b);
}

void add_reb(int a, int b, int c) {
    add(a, b, c);
    add(b, a, 0);
}

bool bfs(int a, int b) {
    for (int i = 0; i < dust.size(); ++i)
        dust[i] = dust.size();
    dust[a] = 0;
    queue<int> q;
    q.push(a);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] && dust[fin[x]] == dust.size()) {
                dust[fin[x]] = dust[v] + 1;
                q.push(fin[x]);
            }
    }
    return !(dust[b] == dust.size());
}

bool dfs(int a, int b) {
    if (a == b)
        return true;
    while (first[a] < g[a].size()) {
        int id = g[a][first[a]];
        if (C[id] - F[id] < 1) {
            ++first[a];
            continue;
        }
        int to = fin[id];
        if (dust[to] != dust[a] + 1) {
            ++first[a];
            continue;
        }
        bool tmp = dfs(to, b);
        if (!tmp) {
            ++first[a];
            continue;
        }
        ++F[id];
        --F[id ^ 1];
        return true;
    }
    return false;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, a, h;
    cin >> n >> m >> a >> h;
    g.resize(n);
    first.resize(n);
    dust.resize(n);
    --a;
    --h;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b)
            continue;
        add_reb(a - 1, b - 1, 1);
    }
    while (timer && bfs(a, h)) {
        for (int i = 0; i < n; ++i)
            first[i] = 0;
        while (timer && dfs(a, h)) {
            --timer;
        }
    }
    if (timer) {
        cout << "NO\n";
        return 0;
    }
    vector<vector<int>> go(n);
    for (int i = 0; i < st.size(); ++i)
        if (F[i] > 0)
            go[st[i]].push_back(fin[i]);
    cout << "YES\n";
    for (int ff = 1; ff < 3; ++ff) {
        vector<int> tmp;
        int v = a;
        while (v != h) {
            tmp.push_back(go[v].back());
            go[v].pop_back();
            v = tmp.back();
        }
        cout << a + 1 << ' ';
        for (auto x : tmp)
            cout << x + 1 << ' ';
        cout << '\n';
    }
    return 0;
}
