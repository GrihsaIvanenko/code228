#include <bits/stdc++.h>

using namespace std;

#define DEBUG

void solve() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    int t;
    cin >> t;
    for (int iter = 0; iter < t; ++iter) {
        int l, r;
        long long k;
        cin >> l >> r >> k;
        long long ans = v[l - 1].first + k * v[l - 1].second - v[l - 1].second;
        for (int i = l; i < r; ++i)
            ans = min(ans, v[i].first + k * v[i].second - v[i].second);
        cout << ans << '\n';
    }
}

int main() {
    #ifdef DEBUG
        freopen("sample.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    solve();
    return 0;
}
