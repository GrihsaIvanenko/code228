#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5, MAXUP = 20;

int anc[MAXN][MAXUP], h[MAXN], up[MAXN][MAXUP], down[MAXN][MAXUP];

vector<int> g[MAXN];

void dfs(int v, int p = 0) {
    anc[v][0] = p;
    h[v] = h[p] + 1;
    for (auto x : g[v])
        if (x != p)
            dfs(x, v);
}

void jump(int &v, int h) {
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h >= (1 << i)) {
            h -= (1 << i);
            v = anc[v][i];
        }
}

int lca(int a, int b) {
    jump(a, h[a] - min(h[a], h[b]));
    jump(b, h[b] - min(h[a], h[b]));
    if (a == b)
        return a;
    for (int i = MAXUP - 1; i >= 0; --i)
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    return anc[a][0];
}

bool can(int a, int b) {
    int cur = 1, c = lca(a, b);
    int h1 = h[a] - h[c];
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h1 >= (1 << i)) {
            cur = min(cur, up[a][i]);
            a = anc[a][i];
            h1 -= (1 << i);
        }
    h1 = h[b] - h[c];
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h1 >= (1 << i)) {
            cur = min(cur, down[b][i]);
            b = anc[b][i];
            h1 -= (1 << i);
        }
    return (cur == 1);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> rebs(n - 1);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
        rebs[i - 1] = {a, b};
    }
    h[0] = -1;
    dfs(0);
    for (int i = 1; i < MAXUP; ++i)
        for (int j = 0; j < n; ++j)
            anc[j][i] = anc[anc[j][i - 1]][i - 1];
    up[0][0] = 1;
    down[0][0] = 1;
    for (int i = 0; i < n - 1; ++i) {
        int fr = rebs[i].first, to = rebs[i].second;
        int it;
        if (h[fr] > h[to])
            it = fr;
        else
            it = to;
        if (h[fr] > h[to]) {
            up[it][0] = 1;
            down[it][0] = 0;
        } else {
            up[it][0] = 0;
            down[it][0] = 1;
        }
    }
    for (int i = 1; i < MAXUP; ++i)
        for (int j = 0; j < MAXN; ++j) {
            up[j][i] = min(up[j][i - 1], up[anc[j][i - 1]][i - 1]);
            down[j][i] = min(down[j][i - 1], down[anc[j][i - 1]][i - 1]);
        }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (can(a, b))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}
