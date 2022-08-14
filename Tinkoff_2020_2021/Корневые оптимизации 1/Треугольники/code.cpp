#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5;

vector<int> g[MAXN], ng[MAXN];

bool cmp(int a, int b) {
    if (g[a].size() != g[b].size())
        return g[a].size() < g[b].size();
    return a < b;
}

int has[MAXN];

void solve() {
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
    for (int i = 0; i < n; ++i) {
        for (auto x : g[i])
            if (cmp(i, x))
                ng[i].push_back(x);
    }
    int ans = 0;
    for (int a = 0; a < n; ++a) {
        for (auto b : ng[a])
            ++has[b];
        for (auto b : ng[a]) {
            for (auto c : ng[b])
                ans += has[c];
        }
        for (auto b : ng[a])
            --has[b];
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
