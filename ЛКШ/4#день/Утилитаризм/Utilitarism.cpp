#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 250000, INF = 1e13;

vector<pair<long long, long long>> dp0, dp1;

vector<pair<long long, long long>> g[MAXN];

void dfs(long long v, long long p, long long mid) {
    dp0[v] = {0, 0};
    dp1[v] = {0, 0};
    for (auto x : g[v]) {
        if (x.first == p) {
           continue;
        }
        dfs(x.first, v, mid);
        dp0[v].first += dp1[x.first].first;
        dp0[v].second += dp1[x.first].second;
    }
    dp1[v] = dp0[v];
    for (auto x : g[v]) {
        if (x.first == p) {
           continue;
        }
        pair<long long, long long> cur = dp0[v];
        cur.first += x.second  + mid + dp0[x.first].first - dp1[x.first].first;
        cur.second += dp0[x.first].second - dp1[x.first].second + 1;
        dp1[v] = max(dp1[v], cur);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    long long n, k;
    cin >> n >> k;
    dp0.resize(n);
    dp1.resize(n);
    for (long long i = 1; i < n; ++i) {
        long long a, b;
        long long cost;
        cin >> a >> b >> cost;
        --a;
        --b;
        g[a].push_back({b, cost});
        g[b].push_back({a, cost});
    }
    long long lb = -INF, rb = INF;
    while (rb - lb > 1) {
        long long mid = (lb + rb) >> 1;
        dfs(0, -1, mid);
        if (dp1[0].second >= k) {
            rb = mid;
        } else {
            lb = mid;
        }
    }
    dfs(0, -1, rb);
    if (dp1[0].second < k && rb == INF) {
        cout << "Impossible\n";
    } else {
        cout << dp1[0].first - (long long)rb * (long long)k << '\n';
    }
    return 0;
}
