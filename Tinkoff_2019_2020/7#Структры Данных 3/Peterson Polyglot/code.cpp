#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000;

int go[MAXN][26], sz[MAXN], d[MAXN];

int ans;

void dfs_calc(int v = 0, int deep = 0) {
    sz[v] = 1;
    d[v] = deep;
    for (auto x : go[v])
        if (x) {
            dfs_calc(x, deep + 1);
            sz[v] += sz[x];
        }
}

vector<int> PTICH(MAXN);

int n;

void priley(int a, int b, vector<pair<pair<int, int>, int>> &cash) {
    for (int i = 0; i < 26; ++i)
        if (go[a][i] == 0) {
            if (go[b][i]) {
                cash.push_back({{a, i}, 0});
                cash.push_back({{a, sz[a]}, -1});
                go[a][i] = go[b][i];
                sz[a] += sz[go[a][i]];
            }
        } else if (go[b][i]) {
            cash.push_back({{a, sz[a]}, -1});
            sz[a] -= sz[go[a][i]];
            priley(go[a][i], go[b][i], cash);
            sz[a] += sz[go[a][i]];
        }
}

void print(int v = 0) {
    cout << v + 1 << " (sz) " << sz[v] << ": ";
    for (int i = 0; i < 26; ++i)
        if (go[v][i])
            cout << char('a' + i) << " " << go[v][i] + 1 << "; ";
    cout << endl;
    for (auto x : go[v])
        if (x)
            print(x);
}

void reshi(int v) {
    int toto = -1;
    for (int i = 0; i < 26; ++i)
        if (go[v][i])
            if (toto == -1 || sz[go[v][i]] > sz[go[v][toto]])
                toto = i;
    if (toto == -1)
        return;
    vector<pair<pair<int, int>, int>> cash;
    for (int i = 0; i < 26; ++i)
        if (go[v][i] && i != toto) {
            priley(go[v][toto], go[v][i], cash);
        }
    PTICH[d[v]] += sz[v] - sz[go[v][toto]];
    reverse(cash.begin(), cash.end());
    for (auto x : cash)
        if (x.second != -1)
            go[x.first.first][x.first.second] = x.second;
        else {
            sz[x.first.first] = x.first.second;
        }
}

void solve() {
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < 26; ++j)
            go[i][j] = 0;
    }
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        --a;
        --b;
        c -= 'a';
        go[a][c] = b;
    }
    dfs_calc();
    for (int i = 0; i < n; ++i)
        reshi(i);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, PTICH[i]);
    }
    cout << n - ans << '\n';
    int uk = 0;
    for (int i = 0; i < n; ++i)
        if (PTICH[i] == ans) {
            cout << i + 1 << '\n';
            return;
        }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
