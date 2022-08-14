#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int le = 0; le < n; ++le) {
            for (int re = le + 1; re <= n; ++re) {
                bool kekw = true;
                for (int pos = le; pos < re; ++pos) {
                    if (v[pos].first > b || v[pos].second < a)
                        kekw = false;
                }
                if (kekw)
                    ans = max(ans, re - le);
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
