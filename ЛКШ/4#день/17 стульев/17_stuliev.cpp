#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int INF = 1e9+7;

void solve() {
    int n;
    cin >> n;
    int d[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
            if (d[i][j] == 0) {
                d[i][j] = INF;
            }
        }
    }
    pair<int, int> dp[1 << n][n];
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = {INF, -1};
        }
   }
   dp[1][0] = {0, 1};
   for (int mask = 2; mask < (1<<n); ++mask) {
        for (int v = 0; v < n; ++v) {
            for (int last = 0; last < n; ++last) {
                if (dp[mask][v].x > dp[mask ^ (1<<v)][last].x + d[last][v] && dp[mask ^ (1<<v)][last].y != -1 && ((1 << v) & mask) && ((1 << last) & mask)) {
                    dp[mask][v].x = dp[mask ^ (1<<v)][last].x + d[last][v];
                    dp[mask][v].y = last;
                }
            }
        }
    }
    vector<int> p;
    for (int i = 0; i < n; ++i) {
        if (dp[(1 << n) - 1][i].x != INF) {
        p.push_back(i);
        }
    }
    if (p.size() == 0) {
        cout << -1;
        return;
    }
    int ans = 0;
    for (int i = 1; i < p.size(); ++i) {
        if (dp[(1 << n) - 1][p[ans]].x > dp[(1 << n) - 1][p[i]].x) {
            ans = i;
        }
    }
    cout << dp[(1 << n) - 1][p[ans]].x << endl;
    vector<int> answer;
    int mask = (1 << n) - 1;
    while (mask != 0) {
        answer.push_back(p[ans]);
        int tmp_mask = mask;
        mask ^= (1 << p[ans]);
        p[ans] = dp[tmp_mask][p[ans]].y;
    }
    reverse(answer.begin(), answer.end());
    for (auto x : answer) {
        cout << x + 1 << " ";
    }
}

int main() {
    solve();
    return 0;
}
