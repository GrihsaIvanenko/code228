#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

vector<int> g[MAXN];

int d[MAXN];

int dfs(int v, int deep = 0, int p = -1) {
    d[v] = deep;
    int cur = v;
    for (auto x : g[v]) {
        if (x == p) {
            continue;
        }
        int res = dfs(x, deep + 1, v);
        if (d[res] > d[cur]) {
           cur = res;
        }
    }
    return cur;
}

int main() {
    for (int i = 0; i < MAXN; ++i) {
        d[i] = 0;
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int v = dfs(0);
    for (int i = 0; i < MAXN; ++i) {
        d[i] = 0;
    }
    cout << d[dfs(v)] << '\n';
    return 0;
}
