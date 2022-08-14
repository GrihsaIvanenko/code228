#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

struct segtree {
    segtree *l = nullptr, *r = nullptr;
    vector<int> numbs;
    segtree (vector<int>& v, int lb = 0, int rb = MAXN) {
        if (lb + 1 == rb) {
            numbs = {v[lb]};
            return;
        }
        int mid = (lb + rb) >> 1;
        l = new segtree(v, lb, mid);
        r = new segtree(v, mid, rb);
        numbs.resize(rb - lb);
        merge(l->numbs.begin(), l->numbs.end(), r->numbs.begin(), r->numbs.end(), numbs.begin());
    }
    void print(int lb = 0, int rb = MAXN) {
        cout << lb << " " << rb << ": ";
        for (auto x : numbs)
            cout << x << " ";
        cout << endl;
        if (lb + 1 == rb)
            return;
        int mid = (lb + rb) >> 1;
        l->print(lb, mid);
        r->print(mid, rb);
    }
    int ask(int le, int re, int lq, int rq, int lb = 0, int rb = MAXN) {
        if (lb >= re || rb <= le)
            return 0;
        if (le <= lb && rb <= re) {
            return upper_bound(numbs.begin(), numbs.end(), rq) - lower_bound(numbs.begin(), numbs.end(), lq);
        }
        int mid = (lb + rb) >> 1;
        return l->ask(le, re, lq, rq, lb, mid) + r->ask(le, re, lq, rq, mid, rb);
    }
};


int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> it(MAXN);
    for (int i = 0; i < n; ++i) {
        cin >> it[i];
    }
    segtree *root = new segtree(it);
    for (int i = 0; i < q; ++i) {
        int le, re, lq, rq;
        cin >> le >> re >> lq >> rq;
        --le;
        cout << root->ask(le, re, lq, rq) << '\n';
    }
    return 0;
}
