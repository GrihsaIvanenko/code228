#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

struct Node{
    int val, y, sz, m, l, r;
    bool sw;
    Node(int val_) {
        val = val_;
        y = rand() << 4 + rand();
        sz = 1;
        m = val_;
        l = -1;
        r = -1;
        sw = 0;
    }
};

struct decart {
    vector<Node*> d;

    int root = -1;

    int sz(int v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sz;
    }

    int m(int v) {
        if (v == -1) {
           return INF;
        }
        return d[v]->m;
    }

    void update(int v) {
        if (v == -1) {
           return;
        }
        d[v]->sz = sz(d[v]->l) + 1 + sz(d[v]->r);
        d[v]->m = min(d[v]->val, min(m(d[v]->l), m(d[v]->r)));
    }

    void prepare(int v) {
        if (v == -1 || !d[v]->sw) {
           return;
        }
        swap(d[v]->l, d[v]->r);
        d[v]->sw = 0;
        if (d[v]->l != -1) {
           d[d[v]->l]->sw ^= 1;
        }
        if (d[v]->r != -1) {
            d[d[v]->r]->sw ^= 1;
        }
    }

    pair<int, int> split(int v, int k) {
        if (v == -1) {
           return {-1, -1};
        }
        prepare(v);
        if (sz(d[v]->l) >= k) {
           pair<int, int> p = split(d[v]->l, k);
           d[v]->l = p.second;
           update(v);
           return {p.first, v};
        }
        pair<int, int> p = split(d[v]->r, k - sz(d[v]->l) - 1);
        d[v]->r = p.first;
        update(v);
        return {v, p.second};
    }

    int merge(int v, int u) {
        if (v == -1) {
           return u;
        }
        if (u == -1) {
           return v;
        }
        prepare(v);
        prepare(u);
        if (d[v]->y > d[u]->y) {
           d[v]->r = merge(d[v]->r, u);
           update(v);
           return v;
        }
        d[u]->l = merge(v, d[u]->l);
        update(u);
        return u;
    }

    void flip(int l, int r) {
        pair<int, int> p = split(root, r);
        pair<int, int> p1 = split(p.first, l - 1);
        if (p1.second != -1) {
           d[p1.second]->sw ^= 1;
        }
        root = merge(p1.first, merge(p1.second, p.second));
    }

    int mm(int l, int r) {
        pair<int, int> p = split(root, r);
        pair<int, int> p1 = split(p.first, l - 1);
        int res = m(p1.second);
        root = merge(p1.first, merge(p1.second, p.second));
        return res;
    }

    void add_back(int val) {
        d.push_back(new Node(val));
        root = merge(root, d.size() - 1);
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    decart d;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        d.add_back(t);
    }
    for (int i = 0; i < m; ++i) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            d.flip(l, r);
        } else {
            cout << d.mm(l, r) << endl;
        }
    }
    return 0;
}
