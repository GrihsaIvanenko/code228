#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

multiset<int> g[MAXN];

vector<pair<int, int>> ans;

void dfs(int v) {
    while (!g[v].empty()) {
        int to = *g[v].begin();
        g[v].erase(g[v].find(to));
        g[to].erase(g[to].find(v));
        dfs(to);
        ans.push_back({v, to});
    }
}

void solve() {
    int n, start = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if (k % 2) {
            start = i;
        }
        for (size_t j = 0; j < k; ++j) {
            int t;
            cin >> t;
            --t;
            g[i].insert(t);
        }
    }
    dfs(start);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    cout << ans[0].first + 1 << " ";
    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i].second + 1 << " ";
    }
    cout << endl;
}

int main() {
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    solve();
    return 0;
}
