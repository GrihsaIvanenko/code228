#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

vector<int> comp(vector<int> &a, vector<int> &b) {
    vector<int> ans(a.size());
    for (int i = 0; i < a.size(); ++i)
        ans[i] = b[a[i]];
    return ans;
}

vector<int> decomp(vector<int> &a, vector<int> &b) {
    vector<int> ans(a.size());
    for (int i = 0; i < a.size(); ++i)
        ans[a[i]] = b[i];
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            --x;
            v[i][j] = x;
        }
    vector<vector<int>> pref(n + 1, vector<int>(m));
    for (int i = 0; i < m; ++i)
        pref[0][i] = i;
    for (int i = 0; i < n; ++i)
        pref[i + 1] = comp(pref[i], v[i]);
    if (m < n) {
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l;
            vector<int> now = decomp(pref[l], pref[r]);
            long long ans = 0;
            for (int i = 0; i < m; ++i)
                ans += (long long)(i + 1) * (now[i] + 1);
            cout << ans << '\n';
        }
    } else {
        vector<vector<long long>> imba(n, vector<long long>(n + 1));
        for (int l = 0; l < n; ++l)
            for (int r = l + 1; r <= n; ++r) {
                vector<int> tmp = decomp(pref[l], pref[r]);
                long long ans = 0;
                for (int i = 0; i < m; ++i)
                    ans += (long long)(i + 1) * (tmp[i] + 1);
                imba[l][r] = ans;
            }
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int a, b;
            cin >> a >> b;
            cout << imba[a - 1][b] << '\n';
        }
    }
}

int main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
