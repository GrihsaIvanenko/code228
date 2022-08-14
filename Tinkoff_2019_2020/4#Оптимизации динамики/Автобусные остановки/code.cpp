#include <bits/stdc++.h>

using namespace std;

const long double INF = 1e18;

long double cost(int l, int r, vector<long double> &pref_sum, vector<long double> &pref_sums) {
    long double x0 = (pref_sum[r] - pref_sum[l]) / (long double)(r - l);
    return (long double)(r - l) * x0 * x0 - (long double)2.0 * x0 * (long double)(pref_sum[r] - pref_sum[l]) +
    (long double)(pref_sums[r] - pref_sums[l]);
}

void solve(int k, int l, int r, int opt_l, int opt_r, vector<long double> &v, vector<vector<long double>>&dp, vector<long double> &pref_sum, vector<long double> &pref_sums) {
    int p = (l + r) / 2;
    int opt_mid = opt_l;
    for (int i = opt_l; i < min(p, opt_r); ++i)
        if (dp[k][p] > dp[k - 1][i] + cost(i + 1, p + 1, pref_sum, pref_sums)) {
            opt_mid  = i;
            dp[k][p] = dp[k - 1][i] + cost(i + 1, p + 1, pref_sum, pref_sums);
        }
    if (l + 1 == r)
        return;
    solve(k, l, p, opt_l, opt_mid + 1, v, dp, pref_sum, pref_sums);
    solve(k, p, r, opt_mid, opt_r, v, dp, pref_sum, pref_sums);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<long double> v(n), prefs(1), prefs_sqares(1);
    prefs.reserve(n + 1);
    prefs_sqares.reserve(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
        prefs_sqares.push_back(prefs_sqares.back() + v[i] * v[i]);
        prefs.push_back(prefs.back() + v[i]);
    }
    vector<vector<long double>> dp(k, vector<long double>(n, INF));
    for (int i = 0; i < n; ++i) {
        dp[0][i] = cost(0, i + 1, prefs, prefs_sqares);
    }
    for (int i = 1; i < k; ++i)
        solve(i, 0, n, 0, n, v, dp, prefs, prefs_sqares);
    cout.precision(10);
    cout << fixed << dp[k - 1][n - 1] << '\n';
    return 0;
}
