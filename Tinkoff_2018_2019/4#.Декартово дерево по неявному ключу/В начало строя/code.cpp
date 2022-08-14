#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y, sz, l, r;
    Node(int x_) {
        x = x_;
        y = rand();
        sz = 1;
        l = -1;
        r = -1;
    }
};

struct decartach {
    vector<Node*> d;

    int root = -1;

    int sz(int v) {
        if (v == -1) {
            return 0;
        }
        return d[v]->sz;
    }

    void update(int v) {
        if (v != -1) {
           d[v]->sz = sz(d[v]->l) + sz(d[v]->r) + 1;
        }
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

    void become_first(int l, int r) {
        pair<int, int> p = split(root, r);
        pair<int, int> p1 = split(p.first, l);
        root = merge(p1.second, merge(p1.first, p.second));
    }

    void print(int A) {
        if(A == -1) {
            return;
        }
        print(d[A]->l);
        cout << d[A]->x << ' ';
        print(d[A]->r);
    }

    void print_them() {
        print(root);
        cout << '\n';
    }

    void add_back(int pos) {
        d.push_back(new Node(pos));
        root = merge(root, d.size() - 1);
    }
};


int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    decartach d;
    for (int i = 0; i < n; ++i) {
        d.add_back(i + 1);
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        d.become_first(l, r);
    }
    d.print_them();
    return 0;
}
