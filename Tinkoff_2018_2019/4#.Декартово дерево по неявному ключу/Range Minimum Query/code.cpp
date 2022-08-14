#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

struct Node{
    int x, y, m, sz, l, r;
    Node(int x_) {
        x = x_;
        y = rand() << 4 + rand();
        m = x;
        sz = 1;
        l = -1;
        r = -1;
    }
};

struct decart {
    vector<Node*> d;

    int root = -1;

    int sz(int A) {
        if (A == -1) {
            return 0;
        }
        return d[A]->sz;
    }

    int mm(int A) {
        if (A == -1) {
           return INF;
        }
        return d[A]->m;
    }

    void update(int A) {
        if (A == -1) {
           return;
        }
        d[A]->sz = sz(d[A]->l) + 1 + sz(d[A]->r);
        d[A]->m = min(d[A]->x, min(mm(d[A]->l), mm(d[A]->r)));
    }

    pair<int, int> split(int A, int k) {
        if (A == -1) {
           return {-1, -1};
        }
        if (sz(d[A]->l) >= k) {
            pair<int, int> p = split(d[A]->l, k);
            d[A]->l = p.second;
            update(A);
            return {p.first, A};
        }
        pair<int, int> p = split(d[A]->r, k - sz(d[A]->l) - 1);
        d[A]->r = p.first;
        update(A);
        return {A, p.second};
    }

    int merge(int A, int B) {
        if (A == -1) {
           return B;
        }
        if (B == -1) {
            return A;
        }
        if (d[A]->y > d[B]->y) {
           d[A]->r = merge(d[A]->r, B);
           update(A);
           return A;
        }
        d[B]->l = merge(A, d[B]->l);
        update(B);
        return B;
    }

    void add(int pos, int val) {
        d.push_back(new Node(val));
        pair<int, int> p = split(root, pos);
        root = merge(p.first, merge(d.size() - 1, p.second));
    }

    int min_on_path(int l, int r) {
        pair<int, int> p = split(root, r);
        pair<int, int> p1 = split(p.first, l - 1);
        int res = mm(p1.second);
        root = merge(p1.first, merge(p1.second, p.second));
        return res;
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    decart d;
    for(int i = 0; i < n; ++i) {
        char type;
        int l, r;
        cin >> type >> l >> r;
        if (type == '+') {
           d.add(l, r);
        } else {
            cout << d.min_on_path(l, r) << '\n';
        }
    }
    return 0;
}
