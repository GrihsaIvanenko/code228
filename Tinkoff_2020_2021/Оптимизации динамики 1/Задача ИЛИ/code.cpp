#include <bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;

const int MAXN = 262144, D = 19;

const ll INF = 1e18;

ll sparce[D][MAXN], val[MAXN], pw[MAXN], pose[MAXN][31], kolvo[MAXN];

pair<ll, int> dodo[MAXN << 1];

void build() {
    for (int i = 0; i < MAXN; ++i)
        sparce[0][i] = val[i];
    for (int i = 1; i < D; ++i)
        for (int j = 0; j + (1 << i) <= MAXN; ++j)
            sparce[i][j] = sparce[i - 1][j] | sparce[i - 1][j + (1 << (i - 1))];
    for (int i = 2; i < MAXN; ++i)
        pw[i] = pw[i - 1] + (((i - 1) & i) == 0);
}

ll get(int l, int r) {
    return sparce[pw[r - l]][l] | sparce[pw[r - l]][r - (1 << pw[r - l])];
}

void calc(int pos) {
    int new_pos = pos;
    pose[pos][kolvo[pos]] = pos + 1;
    ++kolvo[pos];
    while (new_pos != -1) {
        ll val = get(new_pos, pos + 1);
        int lb = -1, rb = new_pos;
        while (rb - lb > 1) {
            int mid = (lb + rb + 1) >> 1;
            ll kekw = get(mid, pos + 1);
            if (kekw == val)
                rb = mid;
            else
                lb = mid;
        }
        pose[pos][kolvo[pos]] = rb;
        ++kolvo[pos];
        new_pos = lb;
    }
    pose[pos][kolvo[pos]] = 0;
    ++kolvo[pos];
    reverse(pose[pos], pose[pos] + kolvo[pos]);
}

pair<ll, int> best(pair<ll, int> a, pair<ll, int> b) {
    if (a.first == b.first) {
        if (a.second < b.second)
            return a;
        return b;
    }
    if (a.first > b.first)
        return a;
    return b;
}

void upd(int i, pair<ll, int> val) {
    i += MAXN;
    dodo[i] = val;
    while (i > 1) {
        i >>= 1;
        dodo[i] = best(dodo[i + i], dodo[i + i + 1]);
    }
}

pair<ll, int> get_zapros(int pos) {
    if (pos == 0)
        return {0, 0};
    pair<ll, int> answ = {-INF, 0};
    pos += MAXN;
    while (pos > 1) {
        if (pos & 1)
            answ = best(answ, dodo[pos - 1]);
        pos >>= 1;
    }
    return answ;
}

pair<ll, int> get_lama(int n, int k, ll straf) {
    for (int i = 0; i < n; ++i) {
        pair<ll, int> answ = {-INF, 0};
        for (int j = 1; j < kolvo[i]; ++j) {
            pair<ll, int> p = get_zapros(pose[i][j] - 1);
            p.first += get(pose[i][j - 1], i + 1);
            ++p.second;
            answ = best(answ, p);
        }
        answ.first -= straf;
        upd(i, answ);
        if (i == n - 1) {
            return answ;
        }
    }
    assert(false);
}

signed main() {
    freopen("t.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN + MAXN; ++i)
        dodo[i] = {-INF, 0};
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> val[i];
    build();
    for (int i = 0; i < n; ++i)
        calc(i);
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < kolvo[i]; ++j)
            cout << pose[i][j] << " ";
        cout << endl;
    }
    ll lb = 0, rb = (1ll) << 32;
    while (rb - lb > 1) {
        ll mid = (lb + rb) >> 1;
        pair<ll, int> p = get_lama(n, k, mid);
        if (p.second >= k)
            lb = mid;
        else
            rb = mid;
    }
    pair<ll, int> p = get_lama(n, k, lb);
    cout << p.first + lb * k << '\n';
    return 0;
}
