#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

void dfs(int a, int b, vector<vector<int>> &v, vector<char> &way) {
    if (a + 1 == b) {
        for (auto x : way)
            cout << x;
        cout << '\n';
    } else {
        way.push_back('0');
        dfs(a, v[a][b], v, way);
        way.back() = '1';
        dfs(v[a][b], b, v, way);
        way.pop_back();
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<long long> v(n);
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF)), sum(n, vector<long long>(n + 1));
    vector<vector<int>> opt(n , vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        cin >> sum[i][i + 1];
        dp[i][i + 1] = 0;
        opt[i][i + 1] = i;
    }
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len;
            sum[l][r] = sum[l][r - 1] + sum[r - 1][r];
            for (int mid = opt[l][r - 1]; mid <= opt[l + 1][r]; ++mid)
                if (dp[l][mid] + dp[mid][r] + sum[l][r] < dp[l][r]) {
                    opt[l][r] = mid;
                    dp[l][r] = dp[l][mid] + dp[mid][r] + sum[l][r];
                }
        }
    }
    vector<char> wy;
    dfs(0, n, opt, wy);
    return 0;
}
