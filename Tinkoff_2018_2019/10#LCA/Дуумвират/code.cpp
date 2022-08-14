#include <bits/stdc++.h>

using namespace std;

const int MAXUP = 22, MAXN = 100001;

int anc[MAXUP][MAXN], d[MAXN];

long long sum[MAXUP][MAXN];

vector<int> g[MAXN];

void dfs(int v, int p = MAXN - 1, int deep = 1) {
    anc[0][v] = p;
    d[v] = deep;
    for (auto x : g[v]) {
        if (x == p) continue;
        dfs(x, v, deep + 1);
    }
}

void up(int &v, int h) {
    for (int i = MAXUP - 1; i >= 0; --i) {
        if ((1 << i) <= h) {
           h -= (1 << i);
           v = anc[i][v];
        }
    }
}

int lca(int a, int b) {
    if (d[a] < d[b]) {
        swap(a, b);
    }
    up(a, d[a] - d[b]);
    if (a == b) {
       return a;
    }
    for (int i = MAXUP - 1; i >= 0; --i) {
        if (anc[i][a] != anc[i][b]) {
           a = anc[i][a];
           b = anc[i][b];
        }
    }
    return anc[0][a];
}

long long sum_on_way(int a, int b) {
    int c = lca(a, b);
    return sum[MAXUP - 1][a] + sum[MAXUP - 1][b] - sum[MAXUP - 1][c] - sum[MAXUP - 1][c] + sum[0][c];
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < MAXUP; ++i) {
        sum[i][MAXN - 1] = 0;
        anc[i][MAXN - 1] = MAXN - 1;
    }
    for (int i = 0; i < n; ++i) {
        cin >> sum[0][i];
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    for (int i = 1; i < MAXUP; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
            sum[i][j] = sum[i - 1][j] + sum[i - 1][anc[i - 1][j]];
        }
    }
   /* for (int i = 0; i < n; ++i) {
        cout << i << " ( " << d[i] << ") : ";
        for(int j = 0; j < 4; ++j) {
            cout << sum[j][i] << " ";
        }
        cout << endl;
    }*/
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        cout << sum_on_way(a, b) << endl;
    }
    return 0;
}
