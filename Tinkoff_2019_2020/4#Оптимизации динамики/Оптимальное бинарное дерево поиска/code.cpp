#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void solve(int n) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 2)), sum(n + 2, vector<int>(n + 2));
    vector<vector<short>> opt(n + 2, vector<short>(n + 2));
    for (int i = 1; i <= n; ++i) {
        cin >> sum[i][i];
        opt[i][i] = i;
        dp[i][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            dp[i][j] = INF;
        }
    }
    for (int len = 1; len < n; ++len) {
        for (int l = 1; l + len <= n; ++l) {
            int r = l + len;
            sum[l][r] = sum[l][r - 1] + sum[r][r];
            for (int k = opt[l][r - 1]; k <= opt[l + 1][r]; ++k) {
                if (dp[l][k - 1] + dp[k + 1][r] + sum[l][k - 1] + sum[k + 1][r] < dp[l][r]) {
                    opt[l][r] = k;
                    dp[l][r] = dp[l][k - 1] + dp[k + 1][r] + sum[l][k - 1] + sum[k + 1][r];
                }
            }
        }
    }
    cout << dp[1][n] << '\n';
    for (int i = 0; i < n + 2; ++i) {
        dp[i].clear();
        dp[i].shrink_to_fit();
        sum[i].clear();
        sum[i].shrink_to_fit();
        opt[i].clear();
        opt[i].shrink_to_fit();
    }
    dp.clear();
    dp.shrink_to_fit();
    sum.clear();
    sum.shrink_to_fit();
    opt.clear();
    opt.shrink_to_fit();
 }

int main () {
    int n;
    while (cin >> n) {
        solve(n);
    }
    return 0;
}
