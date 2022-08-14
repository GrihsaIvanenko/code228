#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5000, INF = 1e9;

vector<int> from, best_dust, used;

int dust(pair<int, int> p1, pair<int, int> p2) {
    return (p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second);
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> coordinats(n);
    for (int i = 0; i < n; ++i) {
        cin >> coordinats[i].first >> coordinats[i].second;
    }
    from.assign(n, -1);
    from[0] = 0;
    used.assign(n, 0);
    best_dust.assign(n, INF);
    for (int useless_counter = 0; useless_counter < n; ++useless_counter) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && (v == -1 || best_dust[i] < best_dust[v])) {
               v = i;
            }
        }
        used[v] = 1;
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
               continue;
            }
            int cur = dust(coordinats[v], coordinats[i]);
            if (best_dust[i] > cur) {
               from[i] = v;
               best_dust[i] = cur;
            }
        }
    }
    long double ans = 0.0;
    for (int i = 0; i < n; ++i) {
        ans += sqrt(dust(coordinats[i], coordinats[from[i]]));
    }
    cout.precision(15);
    cout << fixed << ans << endl;
    return 0;
}
