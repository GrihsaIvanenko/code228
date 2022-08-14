#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int MAXN = 600000, MAXSZ = 200000;

int val[MAXN], push[MAXN], L[MAXN], R[MAXN], SZ[MAXN], timer = 0;

void make_push(int v) {
    if (v == -1 || push[v] == 0)
        return;
    val[v] += push[v];
    if (L[v] != -1)
        push[L[v]] += push[v];
    if (R[v] != -1)
        push[R[v]] += push[v];
    push[v] = 0;
    return;
}

int sz(int v) {
    if (v == -1)
        return 0;
    return SZ[v];
}

void update(int a) {
    if (a == -1)
        return;
    SZ[a] = sz(L[a]) + sz(R[a]) + 1;
}

int merge(int a, int b) {
    if (a == -1)
        return b;
    if (b == -1)
        return a;
    if (rand() % (SZ[a] + SZ[b]) < SZ[b]) {
        make_push(b);
        L[b] = merge(a, L[b]);
        update(b);
        return b;
    }
    make_push(a);
    R[a] = merge(R[a], b);
    update(a);
    return a;
}

pair<int, int> split_by_key(int v, int key) {
    if (v == -1)
        return {-1, -1};
    make_push(v);
    if (val[v] > key) {
        pair<int, int> p = split_by_key(R[v], key);
        R[v] = p.first;
        update(v);
        return {v, p.second};
    }
    pair<int, int> p = split_by_key(L[v], key);
    L[v] = p.second;
    update(v);
    return {p.first, v};
}

pair<int, int> split_by_size(int v, int kolvo) {
    if (v == -1)
        return {-1, -1};
    make_push(v);
    if (sz(L[v]) >= kolvo) {
        pair<int, int> p = split_by_size(L[v], kolvo);
        L[v] = p.second;
        update(v);
        return {p.first, v};
    }
    pair<int, int> p = split_by_size(R[v], kolvo - sz(L[v]) - 1);
    R[v] = p.first;
    update(v);
    return {v, p.second};
}

int make_new(int v) {
    SZ[timer] = 1;
    val[timer] = v;
    return timer++;
}

void print(int v, int flag, int pen = 0) {
    if (v == -1)
        return;
    if (flag) {
        print(R[v], flag, pen + push[v]);
    } else {
        print(L[v], flag, pen + push[v]);
    }
    if (flag && val[v] + push[v] + pen != 0)
        cout << val[v] + push[v] + pen << " ";
    if (flag) {
        print(L[v], flag, pen + push[v]);
    } else {
        print(R[v], flag, pen + push[v]);
    }
}

void printer(int v, int flag = 0) {
    print(v, flag);
    cout << '\n';
}

int Root1 = -1, Root2 = -1;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < MAXSZ; ++i)
        Root2 = merge(Root2, make_new(0));
    for (int i = 0; i < n; ++i) {
        Root1 = merge(Root1, make_new(v[i]));
        pair<int, int> p = split_by_size(Root2, v[i]);
        assert(p.first != -1);
        ++push[p.first];
        Root2 = merge(p.first, p.second);
    }
    for (int i = n; i < MAXSZ; ++i) {
        Root1 = merge(Root1, make_new(0));
    }
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == 't') {
            swap(Root1, Root2);
        } else {
            int x;
            cin >> x;
            if (t == 'a') {
                pair<int, int> p = split_by_key(Root1, x);
                Root1 = merge(p.first, merge(make_new(x), p.second));
                p = split_by_size(Root2, x);
                assert(p.first != -1);
                ++push[p.first];
                Root2 = merge(p.first, p.second);
            } else if (t == 'r') {
                pair<int, int> p = split_by_key(Root1, x);
                pair<int, int> p1 = split_by_key(p.second, x - 1);
                if (sz(p1.first)) {
                    pair<int, int> p2 = split_by_size(p1.first, 1);
                    Root1 = merge(merge(p.first, p2.second), merge(p1.second, make_new(0)));
                    p2 = split_by_size(Root2, x);
                    assert(p2.first != -1);
                    --push[p2.first];
                    Root2 = merge(p2.first, p2.second);
                } else {
                    Root1 = merge(p.first, merge(p1.first, p1.second));
                }
            } else {
                pair<int, int> p = split_by_key(Root1, x);
                pair<int, int> p1 = split_by_key(p.second, x - 1);
                cout << sz(p1.first) << '\n';
                Root1 = merge(p.first, merge(p1.first, p1.second));
            }
        }
    }
    printer(Root1, 1);
}

void precalc() {
    srand(time(nullptr));
    for (int i = 0; i < MAXN; ++i)
        L[i] = R[i] = -1;
}

int main() {
    precalc();
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    solve();
    return 0;
}
