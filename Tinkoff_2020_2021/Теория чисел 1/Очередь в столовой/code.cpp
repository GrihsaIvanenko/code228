#include<bits/stdc++.h>

using namespace std;

using ll =  __int128;

using ld = _Float128;

clock_t fin;

bool is_kvadrat(ll x) {
    ll y = floorf128(powf(x, 1.0/2.0));
    if (y * y == x)
        return true;
    return false;
}

ll gcd(ll A, ll B) {
    if (A < 0)
        A = -A;
    if (B < 0)
        B = -B;
    if (B == 0)
        return A;
    return gcd(B, A % B);
}

ll delit(ll n) {
    ld fn = n;
    ll n13 = floorf128(powf(fn, 1.0 / 3.0));
    for (ll i = 2; i <= n13; ++i)
        if (n % i == 0)
            return i;
    for (ll k = 1; k <= n13; ++k) {
        ll fin_d = floorf(powf(n, 1.0/6.0) / (sqrtf(k) * 4)) + 1;
        for (ll d = 0; d <= fin_d; ++d) {
            // if (clock() > fin)
               // return n;
            ll fkn = 4 * k * n;
            ll tmp = ll(floorf128(sqrtf128(fkn) + d));
            tmp *= tmp;
            tmp -= fkn;
            if (is_kvadrat(tmp)) {
                ll A = floorf128(sqrtf128(fkn)) + d;
                ll B = floorf128(sqrtf128(A * A - fkn));
                ll G = gcd(A + B, n);
                if (G > 1 && G < n)
                    return G;
                G = gcd(A - B, n);
                if (G > 1 && G < n)
                    return G;
            }
        }
    }
    return n;
}

void solve() {
    unsigned long long GG;
    cin >> GG;
    ll n = GG;
    vector<unsigned long long> ans;
    --n;
    while (n > 1) {
        ll cash = delit(n);
        ans.push_back((unsigned long long)cash);
        n /= cash;
    }
    cout << ans.size() << '\n';
    for (int i = ans.size() - 1; i >= 0; --i)
        cout << ans[i] - 1 << ' ';
    cout << '\n';
}

int main() {
    fin = clock() + CLOCKS_PER_SEC * 1.9;
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
