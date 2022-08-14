#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> v(n);
    vector<vector<long long>> dp(n, vector<long long> (n)), sum(n, vector<long long>(n));
    vector<vector<int>> opt(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (int i = 0; i < n; ++i){
        sum[i][i] = v[i];
    }
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j) {
            sum[i][j] = sum[i][j - 1] + sum[j][j];
        }
    }
    for (int i = 0; i < n; ++i){
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int len = 1; len < n; ++len) {
        for (int l = 0; l + len < n; ++l) {
            int r = l + len;
            int lb = opt[l][r - 1], rb = opt[l + 1][r];
            int min_id = lb;
            for (int i = lb; i <= min(rb, r - 1); ++i){
                if (dp[l][i] + dp[i + 1][r] < dp[l][min_id] + dp[min_id + 1][r]) {
                    min_id = i;
                }
            }
            opt[l][r] = min_id;
            dp[l][r] = dp[l][min_id] + dp[min_id + 1][r] + sum[l][r];
        }
    }
    for (int i = 0; i < n; ++i) {
        int l = 0, r = n - 1;
        while (r - l > 0) {
            if (opt[l][r] >= i) {
                cout << '0';
                r = opt[l][r];
            } else {
                cout << '1';
                l = opt[l][r] + 1;
            }
        }
        cout << '\n';
    }
    return 0;
}
