#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001, MAXUP = 20;

int anc[MAXN][MAXUP], p[MAXN], h[MAXN];

int lca(int a, int b) {
    if (h[a] < h[b])
        swap(a, b);
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h[a] - h[b] >= (1 << i))
            a = anc[a][i];
    if (a == b)
        return a;
    for (int i = MAXUP - 1; i >= 0; --i)
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    return anc[a][0];
}

int get(int v) {
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN; ++i)
        p[i] = i;
    h[0] = 0;
    for (int i = 0; i < MAXUP; ++i)
        anc[0][i] = 0;
    int m;
    cin >> m;
    vector<pair<int, pair<int, int>>> asks(m);
    int timer = 1;
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '?') {
            int v, u;
            cin >> v >> u;
            --v;
            --u;
            asks[i] = {0, {v, u}};
        } else if (t == '+') {
            int v;
            cin >> v;
            --v;
            int u = timer++;
            h[u] = h[v] + 1;
            anc[u][0] = v;
            for (int j = 1; j < MAXUP; ++j)
                anc[u][j] = anc[anc[u][j - 1]][j - 1];
            asks[i]  = {1, {v, u}};
        } else {
            int v;
            cin >> v;
            --v;
            asks[i] = {2, {v, 0}};
        }
    }
    for (int i = 0; i < m; ++i) {
        if (asks[i].first == 1)
            continue;
        if (asks[i].first == 2) {
            p[asks[i].second.first] = get(anc[asks[i].second.first][0]);
        } else {
            cout << get(lca(asks[i].second.first, asks[i].second.second)) + 1 << '\n';
        }
    }
    return 0;
}
