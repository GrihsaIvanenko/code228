#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int MAXN = 131072, INF = 1e9 + 7;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b)
        b ^= a ^= b ^= a = a % b;
    return a;
}

vector<int> min1, min2, push, kolvo;

vector<ll> sum;

void update(int v) {
    if (min1[v + v] == min1[v + v + 1]) {
        kolvo[v] = kolvo[v + v] + kolvo[v + v + 1];
        min1[v] = min1[v + v];
        min2[v] = min(min2[v + v], min2[v + v + 1]);
    } else if (min1[v + v] < min1[v + v + 1]) {
        kolvo[v] = kolvo[v + v];
        min1[v] = min1[v + v];
        min2[v] = min(min1[v + v + 1], min2[v + v]);
    } else {
        kolvo[v] = kolvo[v + v + 1];
        min1[v] = min1[v + v + 1];
        min2[v] = min(min2[v + v + 1], min1[v + v]);
    }
    sum[v] = sum[v + v] + sum[v + v + 1];
}

void make_push(int v) {
    if (v + v + 1 < (int)min1.size()) {
        push[v + v] = max(push[v + v], push[v]);
        push[v + v + 1] = max(push[v + v + 1], push[v]);
    }
    if (push[v] <= min1[v])
        return;
    sum[v] += (ll)(push[v] - min1[v]) * kolvo[v];
    min1[v] = push[v];
}

ll get_sum(int le, int re, int lb, int rb, int v) {
    make_push(v);
    if (re <= lb || rb <= le)
        return 0;
    if (le <= lb && rb <= re)
        return sum[v];
    int mid = (lb + rb) >> 1;
    return get_sum(le, re, lb, mid, v + v) + get_sum(le, re, mid, rb, v + v + 1);
}

void max_ravno(int le, int re, int x, int lb, int rb, int v) {
    make_push(v);
    if (re <= lb || rb <= le || min1[v] >= x)
        return;
    if (le <= lb && rb <= re && min2[v] >= x) {
        push[v] = x;
        sum[v] += (ll)(x - min1[v]) * kolvo[v];
        min1[v] = x;
        return;
    }
    int mid = (lb + rb) >> 1;
    max_ravno(le, re, x, lb, mid, v + v);
    max_ravno(le, re, x, mid, rb, v + v + 1);
    update(v);
}

void solve(int n, int k) {
    int sz = 1;
    while (sz < n)
        sz <<= 1;
    min1.assign(sz + sz, 0);
    min2.assign(sz + sz, INF);
    push.assign(sz + sz, 0);
    kolvo.assign(sz + sz, 1);
    sum.assign(sz + sz, 0);
    for (int i = sz - 1; i > 0; --i)
        kolvo[i] = kolvo[i + i] + kolvo[i + i + 1];
    for (int i = 0; i < k; ++i) {
        char t;
        cin >> t;
        if (t == '?') {
            int l, r;
            cin >> l >> r;
            ll a = get_sum(l - 1, r, 0, sz, 1);
            ll b = r - l + 1;
            ll c = gcd(a, b);
            if (b == c) {
                cout << a / c << '\n';
            } else {
                cout << a / c << "/" << b/c << '\n';
            }
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            max_ravno(l - 1, r, x, 0, sz, 1);
        }
    }
}

int main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    while (true) {
        int n, k;
        cin >> n >> k;
        if (n == 0 && k == 0)
            break;
        solve(n, k);
    }
    return 0;
}
