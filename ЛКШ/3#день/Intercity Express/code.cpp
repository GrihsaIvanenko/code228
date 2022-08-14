#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

struct segtree{
    int lb, rb, mid, tmin;
    segtree *l , *r;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        tmin = 0;
    }
    void first_build() {
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            l->first_build();
            r = new segtree(mid, rb);
            r->first_build();
        }
    }
    void print() {
        cout << lb << " " << rb << " : " << tmin << '\n';
        if (rb - lb != 1) {
            l->print();
            r->print();
        }
    }
};

void place(segtree *ideal, segtree *it, int pos, int time) {
    if (it->rb - it->lb == 1) {
        it->tmin = time;
        return;
    }
    if (it->mid > pos) {
        it->l = new segtree(it->lb, it->mid);
        it->r = ideal->r;
        place(ideal->l, it->l, pos, time);
    } else {
        it->l = ideal->l;
        it->r = new segtree(it->mid, it->rb);
        place(ideal->r, it->r, pos, time);
    }
    it->tmin = min(it->l->tmin, it->r->tmin);
}

int go_down(segtree *it, int val) {
    if (it->rb - it->lb == 1) {
        return it->lb;
    }
    if (it->l->tmin <= val) {
        return go_down(it->l, val);
    } else{
        return go_down(it->r, val);
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    int n, s, m;
    cin >> n >> s >> m;
    vector<pair<pair<int, int>, int>> tickets(m);
    map<int, int> compress;
    vector<int> places;
    for (int i = 0; i < m; ++i) {
        int c, a, b;
        cin >> c >> a >> b;
        --c;
        tickets[i] = {{a, b}, c};
        places.push_back(a);
    }
    places.push_back(0);
    sort(places.begin(), places.end());
    places.resize(unique(places.begin(), places.end()) - places.begin());
    sort(tickets.begin(), tickets.end());
    segtree *beg = new segtree(0, MAXN);
    beg->first_build();
    vector<segtree*> roots, tmproots;
    tmproots.push_back(beg);
    for (int i = 0; i < tickets.size(); ++i) {
        if (i == 0 || tickets[i].first.first != tickets[i - 1].first.first) {
            roots.push_back(tmproots.back());
        }
        beg = new segtree(0, MAXN);
        place(tmproots.back(), beg, tickets[i].second, tickets[i].first.second);
        tmproots.push_back(beg);
    }
    roots.push_back(beg);
    int q, p = 0;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a = a + p;
        b = b + p;
        int pos = upper_bound(places.begin(), places.end(), b - 1) - places.begin() - 1;
        if (pos == -1) {
            cout << 1 << '\n';
            p = 1;
        } else if (pos >= roots.size()) {
            cout << 0 << '\n';
            p = 0;
        } else{
            int ans = go_down(roots[pos], a);
            if (ans >= s) {
                cout << 0 << '\n';
                p = 0;
            } else{
                cout << ans + 1 << '\n';
                p = ans + 1;
            }
        }
    }
    return 0;
}
