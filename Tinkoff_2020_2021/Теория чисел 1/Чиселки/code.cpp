#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1e6 + 1e5;

const ll MOD = 1e9 + 7;

ll fact[MAXN], obr[MAXN], lp[MAXN];

ll CCnk(int n, int k) {
    return fact[n + k] * obr[n] % MOD * obr[k] % MOD;
}

ll pw(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

vector<int> simple;

void precalc() {
    fact[0] = obr[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = (fact[i - 1] * (ll)i) % MOD;
        obr[i] = pw(fact[i], MOD - 2);
    }
    for (int i = 2;  i < MAXN; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            simple.push_back(i);
        }
        for (size_t j = 0; j < simple.size() && simple[j] <= lp[i] && i * simple[j] < MAXN; ++j)
            lp[i * simple[j]] = simple[j];
    }
}

ll posch(int steps, int kolvo) {
    if (steps < 0)
        return 0;
    return CCnk(steps, kolvo);
}

void solve() {
    int n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << "1\n";
        return;
    }
    while (simple.back() > n)
        simple.pop_back();
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        vector<pair<int, int>> dels;
        int j = i;
        while (j > 1) {
            if (!dels.size() || dels.back().first != lp[j])
                dels.push_back({lp[j], 0});
            ++dels.back().second;
            j /= lp[j];
        }
        queue<pair<pair<int, int>, pair<int, int>>> q;
        q.push({{0, 0}, {i, 0}});
        while (!q.empty()) {
            int pos = q.front().first.first, kolvo_ban = q.front().first.second,
             num = q.front().second.first, dist = q.front().second.second;
            q.pop();
            if ((unsigned int)pos == dels.size()) {
                ans = (ans + i * posch(k - dist, simple.size() - kolvo_ban)) % MOD;
                continue;
            }
            for (int step = dels[pos].second; step >= 0; --step) {
                q.push({{pos + 1, kolvo_ban}, {num, dist}});
                if (step == dels[pos].second)
                    ++kolvo_ban;
                ++dist;
                num /= dels[pos].first;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    precalc();
    solve();
    return 0;
}
