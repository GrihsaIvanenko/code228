#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e9 + 7, mod = 1000000000;

struct Node{
    long long x, y, l, r, sz;
    long long sum;
    bool del;
    Node(long long x_) {
        x = x_;
        y = rand() << 15 + rand();
        l = -1;
        r = - 1;
        sz = 1;
        sum = x;
    }
};

struct my_set{
    vector<Node*> d;
    vector<long long> free;
    long long root = -1;
    long long sz(long long v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sz;
    }

    long long sm(long long v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sum;
    }

    void update(long long v) {
        if (v == -1) {
           return;
        }
        d[v]->sz = 1 + sz(d[v]->l) + sz(d[v]->r);
        d[v]->sum = d[v]->x + sm(d[v]->l)+ sm(d[v]->r);
    }

    long long begin(long long v) {
        if (v == -1) {
           return -INF;
        }
        if (d[v]->l == -1) {
           return d[v]->x;
        }
        return begin(d[v]->l);
    }

    long long end(long long v) {
        if (v == -1) {
            return -INF;
        }
        if (d[v]->r == -1) {
            return d[v]->x;
        }
        return end(d[v]->r);
    }

    pair<long long, long long> split(long long v, long long x) {
        if (v == -1) {
           return {-1, -1};
        }
        pair<long long, long long> p;
        if (d[v]->x < x) {
            p = split(d[v]->r, x);
            d[v]->r = p.first;
            update(v);
            return {v, p.second};
        } else {
            p = split(d[v]->l, x);
            d[v]->l = p.second;
            update(v);
            return {p.first, v};
        }
    }

    long long merge(long long v, long long u) {
        if (v == -1) {
           return u;
        }
        if (u == -1) {
           return v;
        }
        if (d[v]->y > d[u]->y) {
           d[v]->r = merge(d[v]->r, u);
           update(v);
           return v;
        } else {
            d[u]->l = merge(v, d[u]->l);
            update(u);
            return u;
        }
    }

    void insert(long long x) {
        pair<long long, long long> p = split(root, x);
        pair<long long, long long> p1 = split(p.second, x + 1);
        if (p1.first != -1) {
            root = merge(p.first, merge(p1.first, p1.second));
            return;
        }
        long long id;
        if (free.size() != 0) {
            id = free.back();
           d[free.back()] = new Node(x);
           free.pop_back();
        } else {
            id = d.size();
            d.push_back(new Node(x));
        }
        root = merge(p.first, merge(id, p1.second));
    }

    void delet(long long x) {
        pair<long long, long long> p = split(root, x);
        pair<long long, long long> p1 = split(p.second, x + 1);
        if (p1.first != -1) {
           free.push_back(p1.first);
        }
        root = merge(p.first, p1.second);
    }

    bool exists(long long x) {
        pair<long long, long long> p = split(root, x);
        pair<long long, long long> p1 = split(p.second, x + 1);
        bool res = p1.first != -1;
        root = merge(p.first, merge(p1.first, p1.second));
        return res;
    }

    long long next(long long x) {
        pair<long long, long long> p = split(root, x + 1);
        long long res = begin(p.second);
        root = merge(p.first, p.second);
        return res;
    }

    long long prev(long long x) {
        pair<long long, long long> p = split(root, x);
        long long res = end(p.first);
        root = merge(p.first, p.second);
        return res;
    }

    long long k_elem(long long v, long long k) {
        if (sz(d[v]->l) >= k) {
           return  k_elem(d[v]->l, k);
        }
        if (sz(d[v]->l) == k - 1) {
           return  -d[v]->x;
        }
        return k_elem(d[v]->r, k - 1 - sz(d[v]->l));
    }

    long long sum(long long l, long long r) {
        pair<long long, long long> p = split(root, l);
        pair<long long, long long> p1 = split(p.second, r);
        long long res = 0;
        if (p1.first != -1) {
           res = d[p1.first]->sum;
        }
        root = merge(p.first, merge(p1.first, p1.second));
        return res;
    }

    void print(long long v) {
        if (v == -1) {
           return;
        }
        print(d[v]->l);
        cout << v << ": x " << d[v]->x << "  l " << d[v]->l << "  r " << d[v]->r << " : " << d[v]->sz << " " << d[v]->sum << endl;
        print(d[v]->r);
    }

};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    long long n;
    cin >> n;
    my_set s;
    long long last = 0;
    for (long long i = 0; i < n; ++i) {
        char type;
        long long v;
        cin >> type;
        if (type == '?') {
            long long l, r;
            cin >> l >> r;
            if(r < l) {
                last = 0;
            } else {
                last = s.sum(l, r + 1);
            }
            cout << last << '\n';
        } else {
            long long v;
            cin >> v;
            v = (v + last) % mod;
            s.insert(v);
            last = 0;
        }
    }
    return 0;
}

