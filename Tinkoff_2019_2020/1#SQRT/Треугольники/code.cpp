#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> weight(n);
    vector<pair<int, int>> rebs;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        ++weight[a];
        ++weight[b];
        rebs.push_back({a, b});
    }
    for (auto x : rebs) {
        if (weight[x.first] < weight[x.second])
            g[x.first].push_back(x.second);
        else if (weight[x.first] == weight[x.second])
            g[min(x.first, x.second)].push_back(max(x.first, x.second));
        else
            g[x.second].push_back(x.first);
    }
    vector<int> good(n, -1);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (auto x : g[i])
            good[x] = i;
        for (auto x : g[i])
            for (auto y : g[x])
                if (good[y] == i)
                    ++ans;
    }
    cout << ans << '\n';
    return 0;
}
