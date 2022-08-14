#include <bits/stdc++.h>

using namespace std;

const long long P = 100003, MOD = 1e9 + 9, MAXN = 131072;

long long p[MAXN + 1], sums[MAXN + 1];

struct segtree {
    segtree *l, *r;
    long long val, push;
    int lb, mid, rb;
    segtree (int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        val = 0;
        push = 0;
        if (lb + 1 == rb)
            return;
        l = new segtree(lb, mid);
        r = new segtree(mid, rb);
    }
    void color(int le, int re, int c) {
        if (le >= rb || re <= lb)
            return;
        if (le <= lb && rb <= re) {
            push = c;
            return;
        }
        make_push();
        l->color(le, re, c);
        r->color(le, re, c);
        val = (l->get_val() * p[mid - lb] + r->get_val()) % MOD;
    }
    long long get_val() {
        if (push != 0) {
            return (push * sums[rb - lb]) % MOD;
        }
        return val;
    }
    void make_push() {
        if (push == 0)
            return;
        val = (sums[rb - lb] * push) % MOD;
        if (lb + 1 != rb) {
            l->push = push;
            r->push = push;
        }
        push = 0;
    }
    long long get_hash (int le, int re) {
        if (le >= rb || re <= lb)
            return 0;
        if (le <= lb && rb <= re)
            return (get_val() * p[re - rb]) % MOD;
        make_push();
        return (l->get_hash(le, re) + r->get_hash(le, re)) % MOD;
    }
};

void solve() {
    p[0] = 1;
    sums[0] = 0;
    for (int i = 1; i <= MAXN; ++i) {
        p[i] = (p[i - 1] * P) % MOD;
        sums[i] = (sums[i - 1] + p[i - 1]) % MOD;
    }
    segtree *root = new segtree(0, MAXN);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        root->color(i, i + 1, t);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t) {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            --r;
            int a = root->get_hash(l, l + k), b = root->get_hash(r, r + k);
            if (a == b)
                cout << '+';
            else
                cout << '-';
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            root->color(l, r, k);
        }
    }
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
