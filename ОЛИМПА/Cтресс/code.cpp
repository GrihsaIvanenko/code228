//
// Created by grigo on 22.02.2021.
//

//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace  std;

#define x first
#define  y second

void solve() {
    int n;
    cin >> n;
    ++n;
    vector<pair<int, int>> v(n);
    vector<int> kaka(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x;
        kaka[i] = v[i].x;
        v[i].y = i;
    }
    sort(v.begin(), v.end());
    vector<int> go(n);
    for (int i = 0; i < n; ++i)
        go[v[i].y] = i;
    int now = -1;
    for (int i = 0; i < n; ++i)
        if (kaka[i] == 0)
            now = i;
    now = go[now];
    vector<int> ans;
    while (kaka[now]) {
        ans.push_back(kaka[now]);
        now = go[now];
    }
    reverse(ans.begin(), ans.end());
    cout << n - 1 << endl;
    for (auto x : ans)
        cout << x << ' ';
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
#endif
    int t = 1; // cin >> t;
    while (t--)
        solve();
    return 0;
    return 1;
}

