#include <bits/stdc++.h>

using namespace std;

int val(char t) {
    if (t == '.')
        return 0;
    if (t == 'H')
        return 1;
    if (t == 'O')
        return 2;
    if (t == 'N')
        return 3;
    return 4;
}

int n, m, ST, FIN;

int pos(int x, int y) {
    return x * m + y;
}

bool valid(int x, int y) {
    if (x >= 0)
        if (y >= 0)
            if (x < n)
                if (y < m)
                    return true;
    return false;
}

const int MAXN = 2502;

int timer = 0;

vector<int> g[MAXN], C, F, fin, st, used;

void adda (int a, int b, int c) {
    g[a].push_back(timer);
    C.push_back(c);
    F.push_back(0);
    fin.push_back(b);
    st.push_back(a);
    ++timer;
}

void add(int a, int b, int c) {
    if (c == 0)
        return;
    adda(a, b, c);
    adda(b, a, 0);
}

bool dfs(int v, int FIN) {
    if (v == FIN)
        return true;
    used[v] = true;
    for (auto x : g[v])
        if (C[x] - F[x])
            if (!used[fin[x]])
                if (dfs(fin[x], FIN)) {
                    ++F[x];
                    --F[x ^ 1];
                    return true;
                }
    return false;
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    ST = n * m;
    FIN = n * m + 1;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> v[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if ((i + j) & 1)
                add(ST, pos(i, j),val(v[i][j]));
            else {
                add(pos(i, j), FIN, val(v[i][j]));
                int x = i, y = j;
                if (valid(x - 1, y))
                    add(pos(x - 1, y), pos(x, y), min({1, val(v[x - 1][y]), val(v[x][y])}));
                if (valid(x + 1, y))
                    add(pos(x + 1, y), pos(x, y), min({1, val(v[x + 1][y]), val(v[x][y])}));
                if (valid(x, y - 1))
                    add(pos(x, y - 1), pos(x, y), min({1, val(v[x][y - 1]), val(v[x][y])}));
                if (valid(x, y + 1))
                    add(pos(x, y + 1), pos(x, y), min({1, val(v[x][y + 1]), val(v[x][y])}));
            }
    used.assign(MAXN, 0);
    while (dfs(ST, FIN))
        used.assign(MAXN, 0);
    string YES = "Valid", NO = "Invalid";
    if (g[ST].size() == 0) {
        cout << NO << '\n';
        return 0;
    }
    for (auto x : g[ST])
        if (C[x] - F[x]) {
            cout << NO << '\n';
            return 0;
        }
    for (int i = 0; i < timer; ++i)
        if (fin[i] == FIN)
            if (C[i] - F[i]) {
                cout << NO << '\n';
                return 0;
            }
    cout << YES << '\n';
    return 0;
}
