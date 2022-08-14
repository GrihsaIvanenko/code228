#include <bits/stdc++.h>

using namespace std;

#define DEBUG

vector<long long> C, F, cost, st, fin;

constexpr long long INF = 1e9 + 7;

long long ST, FIN, timer = 0;

vector<long long> dust, from;

vector<vector<long long>> g;

void add(long long a, long long b, long long c, long long d) {
    st.push_back(a);
    fin.push_back(b);
    C.push_back(c);
    F.push_back(0);
    cost.push_back(d);
    g[a].push_back(timer++);
}

void add_reb(long long a, long long b, long long c, long long d) {
    add(a, b, c, d);
    add(b, a, 0, -d);
}

void solve() {
    long long n, k;
    cin >> n >> k;
    g.resize(n + n + 2);
    vector<pair<pair<long long, long long>, pair<long long, long long>>> v(n);
    for (long long i = 0; i < n; ++i) {
        cin >> v[i].first.first >> v[i].second.first >> v[i].second.second;
        v[i].first.second = i;
    }
    sort(v.begin(), v.end());
    ST = n + n + 1, FIN = n + n;
    dust.resize(ST + 1);
    from.resize(ST + 1);
    add_reb(ST, 0, k, 0);
    for (long long i = 0; i < n; ++i) {
        add_reb(i + i, i + i + 2, k, 0);
        int tmp = (upper_bound(v.begin(), v.end(), make_pair(make_pair(v[i].first.first + v[i].second.first,
                    (long long)0), make_pair((long long)0, (long long)0))) - v.begin());
        if (tmp != (int)v.size())
            add_reb(i + i + 1, tmp + tmp, 1, 0);
        add_reb(i + i, i + i + 1, 1, -v[i].second.second);
        add_reb(i + i + 1, FIN, 1, 0);
    }
    while (true) {
        for (long long i = 0; i < (long long)dust.size(); ++i) {
            dust[i] = INF;
            from[i] = -1;
        }
        dust[ST] = 0;
        for (long long i = 0; i < n + n + 2; ++i) {
            for (long long j = 0; j < timer; ++j) {
                if (C[j] - F[j] > 0 && dust[st[j]] != INF && dust[st[j]] + cost[j] < dust[fin[j]]) {
                    dust[fin[j]] = dust[st[j]] + cost[j];
                    from[fin[j]] = j;
                }
            }
        }
        if (dust[FIN] == INF)
            break;
        long long v = FIN;
        while (v != ST) {
            ++F[from[v]];
            --F[from[v] ^ 1];
            v = st[from[v]];
        }
    }
    for (long long id = 0; id < n; ++id) {
        int uk = -1;
        for (int j = 0; j < n; ++j)
            if (v[j].first.second == id)
                uk = j;
        assert(uk != -1);
        for (long long i = 0; i < timer; i += 2) {
            if (st[i] / 2 == fin[i] / 2 && st[i] == uk + uk)
                cout << F[i] << ' ';
        }
    }
    cout << '\n';
}

signed main() {
    #ifndef DEBUGs
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #else
        freopen("t.cpp", "r", stdin);
    #endif
    int t = 1;
    while (t--)
        solve();
    return 0;
}
