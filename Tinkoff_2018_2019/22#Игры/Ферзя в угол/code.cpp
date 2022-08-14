#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("queen1.in", "r", stdin);
    freopen("queen1.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int lose = 1;
            for (int k = 1; k <= j; ++k) lose &= dp[i][j - k];
            for (int k = 1; k <= i; ++k) lose &= dp[i - k][j];
            for (int k = 1; k <= min(i, j); ++k) lose &= dp[i - k][j - k];
            dp[i][j] = 1 - lose;
        }
    }
    cout << 2 - dp.back().back() << endl;
    return 0;
}
