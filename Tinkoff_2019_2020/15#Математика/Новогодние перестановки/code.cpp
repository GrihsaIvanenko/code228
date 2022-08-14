#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18 + 100;

ll mult(ll a, ll b) {
    if (a == 0 || b == 0)
        return 0;
    if (max(a, b) == INF)
        return INF;
    if (a <= INF / b)
        return a * b;
    return INF;
}

ll sum(ll a, ll b) {
    return min(INF, a + b);
}

ll fact(ll n) {
    ll res = 1;
    for (ll i = 1; i <= n; ++i)
        res = mult(res, i);
    return res;
}

ll koef(ll it) {
    return fact(it - 2);
}

/*
1 2 3 4
1 2 4 3
1 3 2 4
1 4 2 3
2 1 3 4
2 1 4 3
3 1 2 4
4 1 2 3
4 3 1 2
*/
void solve() {
    ll n;
    ll k;
    cin >> n >> k;
    --k;
    vector<ll> dp(n + 1);
    dp[0] = 1;
    for (ll i = 1; i <= n; ++i)
        for (ll st = 1; st <= i; ++st)
            dp[i] = sum(dp[i], mult(koef(st), dp[i - st]));
    if (dp.back() <= k) {
        cout << "-1\n";
        return;
    }
    ll add = 0;
    ll ans = -1;
    for (ll st = 1; st <= n; ++st) {
        if (k >= mult(koef(st), dp[n - st]))
            k -= mult(koef(st), dp[n - st]);
        else {
            ans = st;
            break;
        }
    }

    cout << ans << endl;

}

int main() {
    //cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
