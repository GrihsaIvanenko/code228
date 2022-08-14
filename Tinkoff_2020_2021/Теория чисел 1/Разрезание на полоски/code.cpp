#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1e5 + 1;

ll kolvo[MAXN];


int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i <= n; ++i) {
        ll x;
        cin >> x;
        for (int j = 1; j * j <= x; ++j)
            if (x % j == 0) {
                ++kolvo[j];
                if (x / j != j)
                    ++kolvo[x / j];
            }
    }
    for (int i = MAXN - 1; i > 0; --i) {
        if (!kolvo[i])
            continue;
        kolvo[i] = 1;
        for (int j = i + i; j < MAXN; j += i) {
            kolvo[i] -= kolvo[j];
        }
        // cout << i << " " << dp_chet[i] << " " << dp_nechet[i] << endl;
        ans += (kolvo[i]) * i;
    }
    cout << ans - 1 << '\n';
    return 0;
}
