#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

struct segtree{
    int lb, rb, mid, val = 0;
    segtree *l = nullptr, *r = nullptr;
    segtree() {}
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
    }
    void first_build() {
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            l->first_build();
            r = new segtree(mid, rb);
            r->first_build();
        }
    }
    int sum(int le, int re) {
        if (le == re){
            return 0;
        }
        if (le >= rb || re <= lb) {
            return 0;
        }
        if (le <= lb && rb <= re) {
            return val;
        }
        return l->sum(le, re) + r->sum(le, re);
    }
    void upd(segtree *ideal, int pos, int inc) {
        if (lb + 1 == rb) {
            val = ideal->val + inc;
            return;
        }
        if (pos < mid) {
            r = ideal->r;
            l = new segtree(lb, mid);
            l->upd(ideal->l, pos, inc);
        } else{
            l = ideal->l;
            r = new segtree(mid, rb);
            r->upd(ideal->r, pos, inc);
        }
        val = l->val + r->val;
    }
    void print() {
        cout << lb << " " << rb << " " << val << endl;
        if (rb - lb != 1) {
            l->print();
            r->print();
        }
    }
    int get_pos(int k){
        if (rb - lb == 1){
            return lb;
        }
        if (l->val >= k){
            return l->get_pos(k);
        }
        else{
            return r->get_pos(k - l->val);
        }
    }
};

void solve() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> inputs(n);
    vector<int> uks(n), data;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        --t;
        data.push_back(t);
        inputs[t].push_back(i);
    }
    for (int i = 0; i < n; ++i){
        uks[i] = inputs[i].size() - 1;
    }
    vector<segtree*> roots;
    roots.push_back(new segtree(0, MAXN));
    roots.back()->first_build();
    for (int i = m - 1; i >= 0; --i) {
        int it = data[i];
        if (uks[it] == inputs[it].size() - 1) {
            segtree *new_root = new segtree(0, MAXN);
            new_root->upd(roots.back(), inputs[it][uks[it]--], 1);
            roots.push_back(new_root);
        } else{
            segtree *new_root = new segtree(0, MAXN);
            new_root->upd(roots.back(), inputs[it][uks[it] + 1], -1);
            segtree *new_new_root = new segtree(0, MAXN);
            new_new_root->upd(new_root, inputs[it][uks[it]--], 1);
            roots.push_back(new_new_root);
        }
    }
    reverse(roots.begin(), roots.end());
    /*for (int i = 0; i < roots.size(); ++i){
        roots[i]->print();
        cout << endl << endl << endl;
    }*/
    int q, p = 0;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int la = (a + p) % m, ka = (b + p) % n + 1;
        if (roots[la]->sum(la, MAXN) < ka){
            cout << "0\n";
            p = 0;
        }
        else{
            p = roots[la]->get_pos(ka);
            cout << ++p << '\n';
        }
    }
}

int main() {
    solve();
    return 0;
}
