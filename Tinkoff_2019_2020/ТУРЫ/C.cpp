#include <bits/stdc++.h>

using namespace std;

#define ll long
#define endl '\n'
#define F(); cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);

int main () {
    int n, m;
    cin >> n >> m;
    vector<long long> cost(n + n + m + m - 1 - 1);
    for (int i = 0; i < n + n + m + m - 2; ++i)
        cin >> cost[i];
    long long cur_cost = 1e18;
    vector<vector<int>> fl(n, vector<int>(m));
    for (int i = 0; i < (1 << (m + n - 1)); ++i) {
        long long cur = 0;
        for (int j = 0; j < m + n - 1; ++j) {
            if (i & (1 << j)) {
                cur += cost[j];
                int k = m - j;
                for (int h = n - 1; h >= 0; --h) {
                    if (0 <= k && k <= m - 1)
                        fl[h][k] = 1;
                    ++k;
                }
            }
        }
        for (int j = 0; i < n; ++j)
            for (int k = 0; k < m; ++k)
            if (fl[j][k] == 0) {
                cout << n + m - 1 + j + k << endl;
                cur += cost[n + m - 1 + j + k];
                int w = j + i;
                for (int h = n - 1; h >= 0; --h) {
                    if (0 <= w && w <= m - 1)
                        fl[h][w] = 1;
                }
            }
        cur_cost = max(cur_cost, cur);
        for (int j = 0; j < n; ++i)
            for(int k = 0; k < m; ++k)
                fl[j][k] = 0;
    }
    cout << cur_cost << endl;
    return 0;
}
