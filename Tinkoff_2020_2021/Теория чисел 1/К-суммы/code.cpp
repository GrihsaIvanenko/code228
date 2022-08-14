#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e9 + 7;

ll gcd(ll a, ll b) {
    while (b)
        b ^= a ^= b ^= a = a % b;
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll mult(ll a, ll b) {
    if (lcm(a, b) >= INF)
        return INF;
    return lcm(a, b);
}

void norm(ll &x, ll &y, ll s1, ll s2) {
    if (x >= 0) {
        y += x / s1 * s2;
        x %= s1;
    } else {
        y -= (-x + s1 - 1) / s1 * s2;
        x += (-x + s1 - 1) / s1 * s1;
    }
}

ll Egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = Egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    norm(x, y, b / d, a / d);
    return d;
}

signed main() {
    ll n;
    int m;
    cin >> n >> m;
    vector<ll> v(m);
    for (int i = 0; i < m; ++i)
        cin >> v[i];
    ++m;
    for (int i = 0; i < m; ++i)
        if (v[i] == 1) {
            cout << n << '\n';
            return 0;
        }
    v.push_back(n);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    m = v.size();
    ll ans = 0;
    for (int mask_x = 1; mask_x + mask_x < (1 << m); ++mask_x) {
        int NOT_mask = (1 << m) - 1 - mask_x;
        for (int mask_x_1 = NOT_mask; mask_x_1 > 0; mask_x_1 = NOT_mask & (mask_x_1 - 1)) {
            ll proizv_x = 1, proizv_x_1 = 1;
            bool no_solve = false;
            for (int i = 0; i < m; ++i) {
                if ((mask_x >> i) & 1)
                    proizv_x = mult(proizv_x, v[i]);
                if ((mask_x_1 >> i) & 1)
                    proizv_x_1 = mult(proizv_x_1, v[i]);
            }
            if (gcd(proizv_x, proizv_x_1) != 1)
                continue;
            ll X, Y;
            ll cur = Egcd(proizv_x, proizv_x_1, X, Y);
            if (X != 0)
                X = -X + proizv_x_1;
            cur = proizv_x * X;
            if (cur >= n) {
                 cur = 0;
            } else {
                cur = 1 + (n - cur - 1) / proizv_x / proizv_x_1;
            }
            int kolvo = 0;
            for (int i = 0 ; i < m; ++i) {
                if ((mask_x) & (1 << i))
                    ++kolvo;
                if ((mask_x_1) & (1 << i))
                    ++kolvo;
            }
            ans += cur * (1 - 2 * (kolvo & 1));
        }
    }
    cout << ans << '\n';
}
