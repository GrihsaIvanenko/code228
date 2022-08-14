#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072 * 8;

struct segtree {
    segtree *l, *r;
    int mx, push;
    segtree(int lb = -MAXN, int rb = MAXN) {
        mx = 0;
        push = 0;
        if (lb + 1 == rb)
            return;
        int mid = (lb + rb) / 2;
        l = new segtree(lb, mid);
        r = new segtree(mid, rb);
    }
    void update (int lb, int rb) {
        mx += push;
        if (lb + 1 < rb) {
            l->push += push;
            r->push += push;
            push = 0;
            mx = max(l->mx + l->push, r->mx + r->push);
        }
        push = 0;
    }
    void add(int le, int re, int inc, int lb = -MAXN, int rb = MAXN) {
        if (le >= rb || re <= lb)
            return;
        if (le <= lb && rb <= re) {
            push += inc;
            return;
        }
        int mid = (lb + rb) / 2;
        l->add(le, re, inc, lb, mid);
        r->add(le, re, inc, mid, rb);
        update(lb, rb);
    }
    int find_max(int searh, int lb = -MAXN, int rb = MAXN) {
        if (lb + 1 == rb)
            return lb;
        update(lb, rb);
        int mid = (lb + rb) / 2;
        if (l->push + l->mx == searh)
            return l->find_max(searh, lb, mid);
        return r->find_max(searh, mid, rb);
    }
};

int main () {
    int n;
    cin >> n;
    vector<pair<pair<int, int>, pair<int, int>>> events(n + n);
    for (int i = 0; i < n; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events[i + i] = {{a, 1}, {b, d + 1}};
        events[i + i + 1] = {{c + 1, -1}, {b, d + 1}};
    }
    sort(events.begin(), events.end());
    segtree *d = new segtree();
    int x_ans = 0, y_ans = 0, max_k = 0;
    for (auto x : events) {
        //cout << x.first.first << ' ' << x.first.second << ' ' << x.second.first << ' ' << x.second.second << ": ";
        d->add(x.second.first, x.second.second, x.first.second);
        //cout << d->mx + d->push << endl;
        int cur = d->mx + d->push;
        if (cur > max_k) {
            max_k = cur;
            x_ans = x.first.first;
            y_ans = d->find_max(max_k);
        }
    }
    cout << max_k << '\n' << x_ans << ' ' << y_ans << '\n';
    return 0;
}
