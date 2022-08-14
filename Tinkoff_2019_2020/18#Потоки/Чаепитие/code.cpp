#include <bits/stdc++.h>

using namespace std;

vector<int> C, F, first, dust, st, fin;

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

void first_build (vector<int> &kolvo, vector<vector<int>> &good) {
    int n = good.size(), m = kolvo.size();
    S = n + m, T = n + m + 1;
    g.resize(T + 1);
    for (int i = 0; i < n; ++i)
        add_reb(S, i, 0);
    for (int i = 0; i < n; ++i)
        for (auto x : good[i])
            add_reb(i, x + n, kolvo[x]);
    for (int i = 0; i < m; ++i)
        add_reb(i + n, T, kolvo[i]);
    dust.resize(T + 1);
    first.resize(T + 1);
}

bool bfs(int Cmax) {
    for (int i = 0; i < dust.size(); ++i)
        dust[i] = T + 1;
    dust[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] >= Cmax && dust[fin[x]] == T + 1) {
                dust[fin[x]] = dust[v] + 1;
                q.push(fin[x]);
            }
    }
    return !(dust[T] == T + 1);
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

bool can(int wreb) {
    for (int i = 0; i < st.size(); ++i) {
        if (st[i] == S)
            C[i] = wreb;
        F[i] = 0;
    }
    for (int Cmax = 1 << 20; Cmax > 0; Cmax >>= 1)
        while (bfs(Cmax)) {
            for (int i = 0; i < first.size(); ++i)
                first[i] = 0;
            while (dfs(Cmax));
        }
    for (int i = 0; i < st.size(); ++i)
        if (st[i] == S && C[i] != F[i])
            return false;
    return true;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> kolvo(m);
    for (int i = 0; i < m; ++i)
        cin >> kolvo[i];
    vector<vector<int>> good(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        good[i].resize(x);
        for (int j = 0; j < x; ++j) {
            cin >> good[i][j];
            --good[i][j];
        }
    }
    first_build(kolvo, good);
    int lb = 0, rb = 50'000'001;
    for (int mid = lb + rb >> 1; rb - lb > 1; mid = lb + rb >> 1)
        if (can(mid))
            lb = mid;
        else
            rb = mid;
    cout << lb << '\n';
    return 0;
}
