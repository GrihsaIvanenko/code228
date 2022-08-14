#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

void sum(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    map<int, int> mm;
    mm[k - 1] = 1;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    int ans = 1;
    for (int i = 0; i < n; ++i)
        sum(ans, ans);
    for (int i = 0; i < n; ++i) {
        map<int, int> mm1;
        for (auto x = mm.rbegin(); (x != mm.rend()) && (*x).first >= v[i]; ++x)
            sum(mm1[(*x).first / v[i]], (*x).second);
        for (auto x : mm1)
            sum(mm[x.first], x.second);
    }
    for (auto x : mm)
        sum(ans, MOD - x.second);
    cout << ans << '\n';
}
