#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072, SZ = 450, MAXF = 600;

vector<int> g[MAXN], fg[MAXN];

int ft[MAXN], timer = 0, now[MAXN];

unordered_map<int, int> cash[MAXF];

int sum[MAXF];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> now[i];
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i)
        if (g[i].size() >= SZ) {
            ft[i] = timer++;
        }
    assert(timer <= MAXF);
    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (auto x : g[i]) {
            if (ft[x] != -1) {
                fg[i].push_back(x);
                ++cash[ft[x]][now[i]];
                ++sum[ft[x]];
            }
            if (now[x] != now[i] && i < x)
                ++ans;
        }
    cin >> m;
    for (int q = 0; q < m; ++q) {
        int a, z;
        cin >> a >> z;
        --a;
        if (ft[a] != -1) {
            ans -= (sum[ft[a]] - cash[ft[a]][now[a]]);
            for (auto x : fg[a])
                --cash[ft[x]][now[a]];
            now[a] = z;
            ans += (sum[ft[a]] - cash[ft[a]][now[a]]);
            for (auto x : fg[a])
                ++cash[ft[x]][now[a]];
        } else {
            for (auto x : g[a]) {
                if (now[x] != now[a])
                    --ans;
                if (ft[x] != -1)
                    --cash[ft[x]][now[a]];
            }
            now[a] = z;
            for (auto x : g[a]) {
                if (now[x] != now[a])
                    ++ans;
                if (ft[x] != -1)
                    ++cash[ft[x]][now[a]];
            }
        }
        cout << ans << '\n';
    }
}

void precalc() {
    for (int i = 0; i < MAXN; ++i)
        ft[i] = -1;
}

int main() {
    precalc();
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
