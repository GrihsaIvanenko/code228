#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int C = 262144;

struct segtree{
    segtree *l = nullptr, *r = nullptr;
    int lb, rb, mid, val, push;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        val = push = 0;
        if (mid != lb) {
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void update() {
        if (l == nullptr) {
            val += push;
            push = 0;
            return;
        }
        if (push != 0) {
            l->push += push;
            r->push += push;
            push = 0;
        }
        val = max(l->push + l->val, r->push + r->val);
    }
    void plus_(int le, int re, int p) {
        update();
        if (le <= lb && rb <= re) {
            push += p;
            return;
        }
        if (le < mid) {
            l->plus_(le, min(re, mid), p);
        }
        if (re > mid) {
            r->plus_(max(mid, le), re, p);
        }
        update();
    }
    pair<int, int> max_() {
        update();
        if (l == nullptr) {
            return {mid, val};
        }
        if (l->val + l->push >= r->val + r->push)
            return l->max_();
        return r->max_();
    }
    void ccc() {
        cout << lb << " " << rb << " " << val << " " << push << endl;
        if (l != nullptr) {
            l->ccc();
            r->ccc();
        }
    }
};

void solve() {
    segtree *x = new segtree(0, C << 1);
    int n;
    cin >> n;
    vector<pair<pair<int, int>, pair<int, int>>> ev;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ++y2;
        ev.push_back({{x1, 0}, {y1 + C, y2 + C} });
        ev.push_back({{x2, 1}, {y1 + C, y2 + C} });
    }
    sort(ev.begin(), ev.end());
    int max_e = 0;
    int ax = 0, ay = 0;
    for (int i = 0; i < ev.size(); ++i) {
        if (ev[i].x.y == 0)
            x->plus_(ev[i].y.x, ev[i].y.y, 1);
        else
            x->plus_(ev[i].y.x, ev[i].y.y, -1);
        x->update();
       // x->ccc();
        pair<int, int> P = x->max_();
        if (P.y > max_e) {
            max_e = P.y;
            ay = P.x - C;
            ax = ev[i].x.x;
        }
    }
    cout << max_e << '\n' << ax << " " << ay << endl;
}

int main() {
    solve();
    return 0;
}

