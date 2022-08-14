#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

const long long mod = 1e9 + 7;

vector<int> g[MAXN], col(MAXN);

pair<long long, bool> dfs(int v, int p = -1) {
    col[v] = 1;
    int ans = 1;
    bool res = 0;
    for (auto x : g[v]) {
        if (x == p) {
           continue;
        } else if (col[x] == 1) {
            res = 1;
        } else {
            pair<long long, bool> p = dfs(x, v);
            res |= p.second;
            ans += p.first;
        }
    }
    return {ans, res};
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    long long res = 1;
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) {
            pair<long long, bool> p = dfs(i);
            if (p.second) {
               res *= p.first;
               res %= mod;
            }
        }
    }
    cout << res << '\n';
    return 0;
}
