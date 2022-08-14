#include <bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b)
        b ^= a ^= b ^= a = a % b;
    return a;
}

const int MAXN = 65536;

ll seg[MAXN << 1], push[MAXN << 1];

void dpush(int v) {
    push[v + v] += push[v];
    push[v + v + 1] += push[v];
    push[v] = 0;
}

void update(int v) {
    seg[v] = max(seg[v + v] + push[v + v], seg[v + v + 1] + push[v + v + 1]);
}

void add(int le, int re, int val, int lb = 0, int rb = MAXN, int v = 1) {
    if (le >= rb || re <= lb || le == re)
        return;
    if (le <= lb && rb <= re) {
        push[v] += val;
        return;
    }
    dpush(v);
    int mid = (lb + rb) >> 1;
    add(le, re, val, lb, mid, v + v);
    add(le, re, val, mid, rb, v + v + 1);
    update(v);
}

ll get_max(int le, int re, int lb = 0, int rb = MAXN, int v = 1) {
    if (le >= rb || re <= lb)
        return -1e9+7;
    if (le <= lb && rb <= re) {
        return seg[v] + push[v];
    }
    dpush(v);
    update(v);
    int mid = (lb + rb) >> 1;
    return max(get_max(le, re, lb, mid, v + v), get_max(le, re, mid, rb, v + v + 1));
}

vector<pair<pair<int, int>, int>> pref_max, pref_gcd;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    ll ans = 0;
    for (int fin = n - 1; fin >= 0; --fin) {
        int ende = fin + 1;
        while (pref_max.size() && pref_max.back().second <= v[fin]) {
            ende = pref_max.back().first.second;
            add(pref_max.back().first.first, pref_max.back().first.second, pref_max.back().second);
            pref_max.pop_back();
        }
        pref_max.push_back({{fin, ende}, v[fin]});
        if (ende != n)
            add(ende, n, v[fin]);
        ende = fin + 1;
        pref_gcd.push_back({{fin, fin + 1}, v[fin]});
        for (size_t i = 0; i < pref_gcd.size(); ++i)
            pref_gcd[i].second = gcd(pref_gcd[i].second, v[fin]);
        vector<pair<pair<int, int>, int>> ngcd;
        for (size_t i = 0; i < pref_gcd.size(); ++i)
            if (!ngcd.size() || ngcd.back().second != pref_gcd[i].second)
                ngcd.push_back(pref_gcd[i]);
            else
                ngcd.back().first.first = pref_gcd[i].first.first;
        swap(ngcd, pref_gcd);
        for (auto x : pref_gcd)
            ans = max(ans, (ll)x.second * get_max(x.first.first, x.first.second));
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
