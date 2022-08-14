#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll lcm(ll a, ll b) {
    ll c = a * b;
    while (b)
        b ^= a ^= b ^= a = a % b;
    return c / a;
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

ll gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b *y1;
    norm(x, y, b / d, a / d);
    return d;
}

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    ll x, y;
    ll d = gcd(a, b, x, y);
    if (c % d) {
        cout << "Impossible\n";
        return;
    }
    c /= d;
    x *= c;
    y *= c;
    norm(x, y, b / d, a / d);
    cout << x << " " << y << endl;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
