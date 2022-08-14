#include <bits/stdc++.h>

using namespace std;

struct segtree{
    int lb, mid, rb;
    int push;
    segtree *l = nullptr, *r = nullptr;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        push = 0;
        if (lb + 1 != rb) {
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void add(int pos, int val) {
        if (lb + 1 == rb) {
            push = val;
            return;
        }
        if (pos < mid) {
           l->add(pos, val);
        } else {
            r->add(pos, val);
        }
    }
    int val_in_pos(int pos) {
        if (lb + 1 == rb) {
            return push;
        }
        if (pos < mid) {
            return l->val_in_pos(pos) + push;
        } else {
            return r->val_in_pos(pos) + push;
        }
    }
    void pls(int le, int re) {
        if (le >= rb || re <= lb) {
           return;
        }
        if (le <= lb && rb <= re) {
           --push;
            return;
        }
        l->pls(le, re);
        r->pls(le, re);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    segtree *root = new segtree(0, 131072);
    for (int i = 0; i < n; ++i) {
        root->add(i, v[i]);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        int lb = 0, rb = n;
        while (rb - lb > 1) {
            int mid = (lb + rb) >> 1;
            if (root->val_in_pos(mid) < t) {
                lb = mid;
            } else {
                rb = mid;
            }
        }
        if (root->val_in_pos(lb) < t) {
            ++lb;
        }
        cout << n - lb << '\n';
        if (lb != n)root->pls(lb, n);
    }
    return 0;
}
