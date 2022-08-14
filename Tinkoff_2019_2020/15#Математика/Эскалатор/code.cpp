#include <bits/stdc++.h>

using namespace std;

using ld = long double;

int main() {
    int n, t;
    ld p;
    cin >> n >> p >> t;
    vector<vector<ld>> dp(t + 1, vector<ld>(n + 1));
    dp[0][0] = 1.0;
    for (int tim = 1; tim <= t; ++tim) {
        dp[tim][0] = dp[tim - 1][0] * (1.0 - p);
        for (int i = 1; i < n; ++i) {
            dp[tim][i] = dp[tim - 1][i - 1] * p + dp[tim - 1][i] * (1.0 - p);
        }
        dp[tim][n] = dp[tim - 1][n - 1] * p + dp[tim - 1][n];
    }
    ld ans = 0.0;
    for (int i = 0; i <= n; ++i)
        ans += dp.back()[i] * (ld)i;
    cout.precision(10);
    cout << fixed << ans << '\n';
    return 0;
}
