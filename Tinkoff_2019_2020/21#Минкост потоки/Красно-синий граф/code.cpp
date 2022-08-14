#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 1e9 + 7;

int get (int v, vector<int> &p) {
    if (p[v] == v)
        return v;
    return p[v] = get(v, p);
}

void unite (int a, int b, vector<int> &p) {
    a = get(a, p);
    b = get(b, p);
    p[a] = b;
}

void silly(int n) {
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> g[i][j];
    int a, b;
    cin >> a >> b;
    int ans = INF;
    for (int mask = 0; mask < (1 << n * (n - 1)); ++mask) {
        vector<int> p1(n), p2(n);
        for (int i = 0; i < n; ++i)
            p1[i] = p2[i] = i;
        int timer = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j){
                if ((1 << timer) & mask)
                    unite(i, j, p1);
                else
                    unite(i, j, p2);
                ++timer;
            }
        int aa = 1, bb = 1, anc1 = get(0, p1), anc2 = get(0, p2);
        for (int i = 1; i < n; ++i) {
            aa = min(aa, int(anc1 == get(i, p1)));
            bb = min(bb, int(anc2 == get(i, p2)));
        }
        if (aa == a && bb == b) {
            int cur = 0;
            timer = -1;
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j, ++timer)
                    if ((((1 << timer) & mask) > 0) != g[i][j])
                        ++cur;
            ans = min (ans, cur);
        }
    }
    if (ans == INF) {
        cout << "-1\n";
        return;
    }
    for (int mask = 0; mask < (1 << n * (n - 1)); ++mask) {
        vector<int> p1(n), p2(n);
        for (int i = 0; i < n; ++i)
            p1[i] = p2[i] = i;
        int timer = -1;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j, ++timer)
                if ((1 << timer) & mask)
                    unite(i, j, p1);
                else
                    unite(i, j, p2);
        int aa = 1, bb = 1, anc1 = get(0, p1), anc2 = get(0, p2);
        for (int i = 1; i < n; ++i) {
            aa = min(aa, int(anc1 == get(i, p1)));
            bb = min(bb, int(anc2 == get(i, p2)));
        }
        if (aa == a && bb == b) {
            int cur = 0;
            timer = -1;
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j, ++timer)
                    if ((((1 << timer) & mask) > 0) != g[i][j])
                        ++cur;
            if (ans == cur) {
                cout << ans << '\n';
                timer = -1;
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j, ++timer)
                    if ((((1 << timer) & mask) > 0) != g[i][j])
                        cout << i + 1 << ' ' << j + 1 << '\n';
            }
            return;
        }
    }
    assert(false);
}

void solve() {
    int n;
    cin >> n;
    if (n <= 7) {
        silly(n);
        return;
    }
    assert(false);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t;//cin >> t;
    while (t--)
        solve();
    return 0;
}
