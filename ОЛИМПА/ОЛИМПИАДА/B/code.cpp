#include <bits/stdc++.h>

using namespace std;

#define int long long

void gg() {
    cout << "-1\n";
    exit(0);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;
    for (auto x : v) {
        if ((x.second - x.first + 1000000000ll) % 2 != 0)
            gg();
    }
    for (int i = 1; i < n; ++i) {
        int dx = abs(v[i].second - v[i - 1].second);
        int dy = v[i].first - v[i - 1].first;
        if (dy < dx)
            gg();
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        pair<int, int> prev = {0, 0};
        if (i != 0)
            prev = v[i - 1];
        int days = v[i].first - prev.first;
        int cost = v[i].second - prev.second;
        if (days == cost) {
            ans.push_back({days, -1});
        } else if (days == -cost) {
            ans.push_back({-1, days});
        } else {
            ans.push_back({(days + cost) / 2, (days - cost) / 2});
        }
    }
    vector<pair<int, char>> answ;
    if (ans[0].first == -1) {
        answ.push_back({ans[0].second, '-'});
    } else if (ans[0].second == -1) {
        answ.push_back({ans[0].first, '+'});
    } else {
        int up = 0;
        for (int i = 0; i < n; ++i)
            if (ans[i].first == -1) {
                up = i % 2;
                break;
            } else if (ans[i].second == -1) {
                up = 1 - i % 2;
                break;
            }
        answ.push_back({ans[0].first, '+'});
        answ.push_back({ans[0].second, '-'});
        if (!up)
            swap(answ[0], answ[1]);
    }
    for (int i = 1; i < n; ++i) {
        if (ans[i].first == -1) {
            if (answ.back().second == '-')
                answ.back().first += ans[i].second;
            else
                answ.push_back({ans[i].second, '-'});
        } else if (ans[i].second == -1) {
            if (answ.back().second == '+')
                answ.back().first += ans[i].first;
            else
                answ.push_back({ans[i].first, '+'});
        } else {
            if (answ.back().second == '+') {
                answ.back().first += ans[i].first;
                answ.push_back({ans[i].second, '-'});
            } else {
                answ.back().first += ans[i].second;
                answ.push_back({ans[i].first, '+'});
            }
        }
    }
    cout << answ.size() << '\n';
    for (auto x : answ)
        cout << x.first << " " << x.second << '\n';
}

signed main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    int t = 1; // cin >> t;
    while (t--)
        solve();
    return 0;
}
