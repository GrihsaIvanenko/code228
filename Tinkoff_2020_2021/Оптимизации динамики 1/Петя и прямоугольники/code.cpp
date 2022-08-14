#include <bits/stdc++.h>

using namespace std;

vector<pair<long long, pair<long long, long long>>> hull;

long long intersect(pair<long long, long long> a, pair<long long, long long> b) {
    long long dk = a.first - b.first;
    long long db = b.second - a.second;
    return (db + dk - 1) / dk;
}

void add(long long k, long long b) {
    while (hull.size() && hull.back().first >= intersect(hull.back().second, {k, b}))
        hull.pop_back();
    long long act = 0;
    if (hull.size())
        act = intersect(hull.back().second, {k, b});
    hull.push_back({act, {k, b}});
}

long long get(int x) {
    int lb = 0, rb = hull.size();
    while (rb - lb > 1) {
        int mid = (lb + rb) / 2;
        if (hull[mid].first <= x)
            lb = mid;
        else
            rb = mid;
    }
    return hull[lb].second.first * x + hull[lb].second.second;
}

int main() {
    //  freopen("t.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    vector<pair<int, int>> val;
    for (int i = 0; i < n; ++i) {
        while (val.size() && val.back().second <= v[i].second)
            val.pop_back();
        val.push_back(v[i]);
    }
    long long ans = 0;
    for (auto x : val) {
        add(x.second, ans);
        ans = get(x.first);
    }
    cout << ans << '\n';
    return 0;
}
