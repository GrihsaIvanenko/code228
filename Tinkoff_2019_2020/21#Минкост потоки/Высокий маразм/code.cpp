#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 500 * 500 + 2, INF = 1e9 + 7;

vector<pair<int, int>> g[MAXN];

int dust[MAXN];

void solve() {
    for (int i = 0; i < MAXN; ++i)
        dust[i] = INF;
    int n;
    cin >> n;
    //assert(n < 2);
    for (int x = 0; x <= n; ++x)
        for (int y = 0; y < n; ++y) {
            int z;
            cin >> z;
            int st = x * n + y;
            if (x == n)
                st = MAXN - 2;
            int fin = (x - 1) * n + y;
            if (x == 0)
                fin = MAXN - 1;
            g[st].push_back({fin, z});
        }
    for (int x = 0; x < n; ++x)
        for (int y = 0; y <= n; ++y) {
            int z;
            cin >> z;
            int st = x * n + y - 1;
            if (y == 0)
                st = MAXN - 2;
            int fin = x * n + y;
            if (y == n)
                fin = MAXN - 1;
            g[st].push_back({fin, z});
        }
    for (int x = 0; x <= n; ++x)
        for (int y = 0; y < n; ++y) {
            int z;
            cin >> z;
            int st = (x - 1) * n + y;
            if (x == 0)
                st = MAXN - 1;
            int fin = x * n + y;
            if (x == n)
                fin = MAXN - 2;
            g[st].push_back({fin, z});
        }
    for (int x = 0; x < n; ++x)
        for (int y = 0; y <= n; ++y) {
            int z;
            cin >> z;
            int st = x * n + y;
            if (y == n)
                st = MAXN - 1;
            int fin = x * n + y - 1;
            if (y == 0)
                fin = MAXN - 2;
            g[st].push_back({fin, z});
        }
    set<pair<int, int>> q;
    dust[MAXN - 2] = 0;
    q.insert({dust[MAXN - 2], MAXN - 2});
    while (q.size()) {
        int v = (*q.begin()).second;
        q.erase(*q.begin());
        for (auto x : g[v])
            if (dust[x.first] > x.second + dust[v]) {
                q.erase({dust[x.first], x.first});
                dust[x.first] = x.second + dust[v];
                q.insert({dust[x.first], x.first});
            }
    }
    cout << dust[MAXN - 1] << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;//cin >> t;
    while (t--)
        solve();
    return 0;
}
