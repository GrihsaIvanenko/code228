#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e6 + 1;

using ll = long long;

const ll INF = 1e9 + 7;

vector<int> simple;

int lp[MAXN];
ll g[MAXN], ans[MAXN];

void gen(int x) {
    vector<pair<int, int>> parts;
        while (x != 1) {
            if (!parts.size() || parts.back().first != lp[x])
                parts.push_back({lp[x], 0});
            ++parts.back().second;
            x /= lp[x];
        }
    queue<pair<int, int>> res;
    res.push({0, 1});
    while (!res.empty()) {
        unsigned int pos = res.front().first, has = res.front().second;
        res.pop();
        if (pos == parts.size()) {
            ++g[has];
        } else {
            for (int i = 0; i <= parts[pos].second; ++i) {
                res.push({pos + 1, has});
                has *= parts[pos].first;
            }
        }
    }
}

ll pw(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = (ans * a) % INF;
        a = (a * a) % INF;
        b >>= 1;
    }
    return ans;
}


void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x == 1)
            continue;
        gen(x);
    }
    ll answer = 0;
    for (int i = MAXN - 1; i > 1; --i) {
        if (!g[i])
            continue;
        ans[i] = pw(2, g[i] - 1) * g[i] % INF;
        for (int j = i * 2; j < MAXN; j += i) {
            ans[i] = (ans[i] - ans[j] + INF) % INF;
        }
        answer = (answer + ans[i] * i) % INF;
    }
    cout << answer << '\n';
}

void precalc() {
    memset(lp, 0, sizeof(lp));
    memset(g, 0, sizeof(g));
    for (int i = 2; i < MAXN; ++i) {
        if (!lp[i]) {
            simple.push_back(i);
            lp[i] = i;
        }
        for (size_t j = 0; j < simple.size() && simple[j] * i <= MAXN && simple[j] <= lp[i]; ++j)
            lp[i * simple[j]] = simple[j];
    }
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    precalc();
    solve();
    return 0;
}
