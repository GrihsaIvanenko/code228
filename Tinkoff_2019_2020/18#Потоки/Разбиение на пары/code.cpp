#include <bits/stdc++.h>

using namespace std;

vector<int> C, F, st, fin, dust, first;

vector<vector<int>> g;

int S, T;

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

bool friends(int a, int b, int k) {
    if (!k)
        return true;
    if (a % 3 == b % 3 && b % 3 != 1)
        return false;
    return friends(a / 3, b / 3, k - 1);
}

bool bfs(int Cmax) {
    for (int i = 0; i < dust.size(); ++i)
        dust[i] = dust.size();
    dust[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] >= Cmax && dust[fin[x]] == dust.size()) {
                dust[fin[x]] = dust[v] + 1;
                q.push(fin[x]);
            }
    }
    return !(dust[T] == dust.size());
}

bool dfs(int Cmax, int v = S) {
    if (v == T)
        return true;
    while (first[v] < g[v].size()) {
        int id = g[v][first[v]];
        if (C[id] - F[id] < Cmax) {
            ++first[v];
            continue;
        }
        int to = fin[id];
        if (dust[to] != dust[v] + 1) {
            ++first[v];
            continue;
        }
        bool tmp = dfs(Cmax, to);
        if (!tmp) {
            ++first[v];
            continue;
        }
        F[id] += Cmax;
        F[id ^ 1] -= Cmax;
        return true;
    }
    return false;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> par(n, vector<int>(k));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            cin >> par[i][j];
    vector<vector<int>> by_types(k, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            by_types[j][i] = par[i][j];
    for (int i = 0; i < k; ++i)
        sort(by_types[i].begin(), by_types[i].end());
    vector<int> medians(k);
    vector<bool> goods(k);
    for (int i = 0; i < k; ++i) {
        medians[i] = by_types[i][n / 2];
        goods[i] = (by_types[i][n / 2] == by_types[i][n / 2 - 1]);
    }
    int N = 2;
    for (int i = 1; i < k; ++i)
        N += (N << 1);
    vector<vector<int>> mem(N);
    for (int i = 0; i < n; ++i) {
        int id = (par[i][0] >= medians[0]);
        for (int j = 1; j < k; ++j) {
            id += (id << 1);
            if (par[i][j] == medians[j] && goods[j])
                ++id;
            else if (par[i][j] >= medians[j])
                id += 2;
        }
        mem[id].push_back(i);
    }
    S = N, T = N + 1;
    g.resize(T + 1);
    dust.resize(T + 1);
    first.resize(T + 1);
    for (int i = 0; i + i < N; ++i) {
        add_reb(S, i, mem[i].size());
        add_reb(i + (N >> 1), T, mem[i + (N >> 1)].size());
        for (int j = (N >> 1); j < N; ++j)
            if (friends(i, j - (N >> 1), k - 1)) {
                add_reb(i, j, min(mem[i].size(), mem[j].size()));
            }
    }
    bool fff = false;
    for (int Cmax = (1 << 20); Cmax > 0; Cmax >>= 1)
        while (bfs(Cmax)) {
            for (int i = 0; i < N + 2; ++i)
                first[i] = 0;
            while (dfs(Cmax));
        }
    int tmp = 0;
    for (auto x : g[S])
        tmp += F[x];
    if (tmp + tmp != n) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < st.size(); i += 2)
        if (st[i] != S && fin[i] != T) {
            while (min(F[i], (int)min(mem[st[i]].size(), mem[fin[i]].size()))) {
                cout << mem[st[i]].back() + 1 << ' ' << mem[fin[i]].back() + 1 << '\n';
                mem[st[i]].pop_back();
                mem[fin[i]].pop_back();
                --F[i];
            }
        }
    return 0;
}
