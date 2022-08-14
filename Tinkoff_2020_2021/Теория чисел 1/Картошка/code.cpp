#include <bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;
    int m1 = m;
    vector<ll> q;
    for (int i = 2; i * i <= m; ++i) {
        if (m % i == 0) {
            q.push_back(i);
            while (m % i == 0)
                m /= i;
        }
    }
    if (m > 1)
        q.push_back(m);
    m = m1;
    ll ans = 0;
    for (int mask = 0; mask < (1 << q.size()); ++mask) {
        ll kolvo = 0, chis = 1;
        for (int i = 0; i < q.size(); ++i)
            if (mask & (1 << i)) {
                ++kolvo;
                chis *= q[i];
            }
        ans += (1 - 2 * (kolvo & 1)) * (n / chis);
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
