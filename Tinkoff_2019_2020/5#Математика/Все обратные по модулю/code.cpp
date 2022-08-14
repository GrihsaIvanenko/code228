#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e8 + 1;

int fact[MAXN];

int pw(int x, int y, int p) {
    if (y == 0)
        return 1;
    if (y % 2)
        return ((long long)x * (long long)pw(x, y - 1, p)) % (long long)p;
    return pw(((long long)x * (long long)x) % (long long)p, y/2, p);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int p;
    cin >> p;
    if (p == 1) {
        cout << 0;
        return 0;
    }
    fact[1] = 1;
    for (int i = 2; i < p; ++i)
        fact[i] = ((long long)fact[i - 1] * (long long)i) % (long long)p;
    int res = pw(fact[p - 1], p - 2, p);
    for (int i = p - 1; i > 0; --i) {
        fact[i] = res;
        res = ((long long)res * (long long)i) % (long long)p;
    }
    int tmp = 1, ans = 0;
    for (int i = 1; i < p; ++i) {
        ans += ((long long)fact[i] * (long long)tmp) % (long long)p;
        if (ans >= p)
            ans -= p;
        tmp = ((long long)tmp * (long long)i) % (long long)p;
        if (i % 100 == 0) {
            cout << ans % p << ' ';
            ans = 0;
        }
    }
    if (p % 100 != 1)cout << ans << '\n';
    return 0;
}
