#include <bits/stdc++.h>

using namespace std;

#define int long long

#define x first
#define y second

const int INF = 1e18 + 7;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].x >> v[i].y;
    int q;
    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --c;
        int ans = INF;
        for (int i = a; i < b; ++i)
            ans = min(ans, v[i].x + v[i].y * c);
        cout << ans << '\n';
    }
}
