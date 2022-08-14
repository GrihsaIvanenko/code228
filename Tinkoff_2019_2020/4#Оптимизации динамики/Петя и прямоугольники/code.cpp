#include <bits/stdc++.h>

using namespace std;

long long intersect(long long k1, long long b1, long long k2, long long b2) {
    return (b1 - b2 + k2 - k1 - 1ll) / (k2 - k1);
}

int main () {
    cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    vector<pair<long long, long long>> goods = {v.back()};
    int max_y = v.back().second;
    for (int i = n - 2; i >= 0; --i)
        if (max_y < v[i].second) {
            goods.push_back(v[i]);
            max_y = v[i].second;
        }
    goods.push_back({0, 1000000000});
    goods.push_back({0, 1000000000});
    reverse(goods.begin(), goods.end());
    //for (auto x : goods)cout << x.first << " goods " << x.second << endl;
    vector<long long> dp(goods.size());
    vector<pair<pair<long long, long long>, long long>>  lines = {{{1000000000, 0}, -1000000000000000000ll}};
    for (int i = 2; i < goods.size(); ++i) {
        int l = 0, r = lines.size();
        while (r - l > 1) {
            int mid = (r + l) >> 1;
            if (lines[mid].second <= goods[i].first)
                l = mid;
            else
                r = mid;
        }
        long long cost_before = lines[l].first.second;
        if (cost_before + lines[l].first.first * goods[i].first > dp[i - 1] + goods[i].first * goods[i].second) {
            cost_before = dp[i - 1];
            dp[i] = cost_before + goods[i].first * goods[i].second;
        } else {
            dp[i] = cost_before + lines[l].first.first * goods[i].first;
        }
        while(intersect(goods[i].second, dp[i - 1], lines.back().first.first, lines.back().first.second) <= lines.back().second)
            lines.pop_back();
        lines.push_back({{goods[i].second, dp[i - 1]},
            intersect(goods[i].second, dp[i - 1], lines.back().first.first, lines.back().first.second)});
        //for (auto x : lines) cout << x.first.first << " lines " << x.first.second << " " << x.second << endl;cout << endl;
    }
    //for (auto x : dp) cout << x << " dp "; cout << endl;
    cout << dp.back() << '\n';
    return 0;
}
