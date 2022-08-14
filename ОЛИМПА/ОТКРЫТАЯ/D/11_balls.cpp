#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;

vector<int> g[MAXN];

char my[MAXN];

long long ans = 0;

string s;

void dfs(int v, string &res, int p = -1) {
    res.push_back(my[v]);
    if (res <= s)
        ++ans;
    for (auto x : g[v])
        if (x != p)
            dfs(x, res, v);
    res.pop_back();
}

void solve() {
    int n, m;
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < n; ++i)
        cin >> my[i];
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    string res = "";
    for (int i = 0; i < n; ++i)
        dfs(i, res);
    cout << ans << '\n';
}

int main() {
    freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
