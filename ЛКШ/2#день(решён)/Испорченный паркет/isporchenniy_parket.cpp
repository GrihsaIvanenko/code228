#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300 * 300, mlp = 300;

int mt[MAXN], used[MAXN], timer = 1;

vector<int> g[MAXN];

bool dfs(int v) {
    if (used[v] == timer) {
        return false;
    }
    used[v] = timer;
    for (auto x : g[v]) {
        if (mt[x] == -1) {
            mt[x] = v;
            return true;
        }
    }
    for (auto x : g[v]){
         if (dfs(mt[x])) {
            mt[x] = v;
            return true;
        }
    }
    return false;
}

int n, m, a, b;

bool mp[MAXN];

void solve() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    for (int i = 0; i < MAXN; ++i) {
        mt[i] = -1;
        mp[i] = used[i] = 0;
    }
    cin >> n >> m >> a >> b;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char t;
            cin >> t;
            if (t == '*'){
                mp[mlp * i + j] = 1;
            }
            else{
                mp[mlp * i + j] = 0;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2) {
                if (mp[mlp * i + j]) {
                    if (i != 0 && mp[mlp * (i - 1) + j]) {
                        g[mlp * i + j].push_back(mlp * (i - 1) + j);
                    }
                    if (i != mlp - 1 && mp[mlp * (i + 1) + j]) {
                        g[mlp * i + j].push_back(mlp * (i + 1) + j);
                    }
                    if (j != 0 && mp[mlp * i + j - 1]) {
                        g[mlp * i + j].push_back(mlp * i + j - 1);
                    }
                    if (j != mlp - 1 && mp[mlp * i + j + 1]) {
                        g[mlp * i + j].push_back(mlp * i + j + 1);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2) {
                dfs(i * mlp + j);
                timer++;
            }
        }
    }
    int ans = 0;
    int tt = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (mt[i] != -1) {
            ans += min(a, b + b);
            tt-= 2;
        }
        if (mp[i]) {
            ++tt;
        }
    }
    ans += tt * b;
    cout << ans;
}

signed main() {
    solve();
    return 0;
}
