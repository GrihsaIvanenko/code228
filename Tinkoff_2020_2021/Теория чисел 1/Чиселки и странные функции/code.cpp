#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll f(ll x) {
    vector<pair<ll, int>> p;
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            p.push_back({i, 0});
            while (x % i == 0) {
                ++p.back().second;
                x /= i;
            }
        }
    }
    if (x != 1)
        p.push_back({x, 1});
    ll ans = 1;
    for (int i = 0; i < p.size(); ++i) {
        ans *= (p[i].first - 1);
        for (int j = 1; j < p[i].second; ++j)
            ans *= p[i].first;
    }
    return ans;
}

signed main() {
    ll n, k;
    cin >> n >> k;
    k = (k + 1ll)>>1;
    for (int i = 0; i < k; ++i) {
        n = f(n);
        if (n == 1)
            break;
    }
    cout << n % (100000007ll) << '\n';
    return 0;
}
