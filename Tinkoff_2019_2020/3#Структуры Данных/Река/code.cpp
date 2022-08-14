#include <bits/stdc++.h>

using namespace std;

struct Node {
    int sz, s, f, y, l, r;
    Node(int start, int finish) {
        s = start;
        f = finish;
        y = rand() << 4 + rand();
        l = -1;
        r = -1;
        sz = 1;
    }

    void add(int ll, int rr) {
        if (ll == f) {
            f = rr;
        }
        if  (rr == s) {
            s = ll;
        }
    }

};

struct decart {
    vector<Node*> d;

    vector<int> free;

    int root = -1;

    long long nalog = 0;

    int sz(int v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sz;
    }

    long long len(int v) {
        if (v == -1) {
           return 0;
        }
        long long res = d[v]->f - d[v]->s;
        return res * res;
    }

    void update(int v) {
        if (v == -1) {
           return;
        }
        d[v]->sz = sz(d[v]->l) + 1 + sz(d[v]->r);
    }

    pair<int, int> split(int v, int k) {
        if (v == -1) {
           return {-1, -1};
        }
        if  (sz(d[v]->l) >= k) {
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
        if (d[v]->y > d[u]->y) {
           d[v]->r = merge(d[v]->r, u);
           update(v);
           return v;
        }
        d[u]->l = merge(v, d[u]->l);
        update(u);
        return u;
    }

    int begin(int v) {
        if (v == -1) {
           return -1;
        }
        if (d[v]->l == -1) {
            return v;
        }
        return begin(d[v]->l);
    }

    int end(int v) {
        if (v == -1) {
           return -1;
        }
        if (d[v]->r == -1) {
           return v;
        }
        return end(d[v]->r);
    }

    int new_v(int s, int f) {
        int res = d.size();
        if (free.size() != 0) {
            res = free.back();
            free.pop_back();
            d[res] = new Node(s, f);
        } else {
            d.push_back(new Node(s, f));
        }
        return res;
    }

    void rip(int v) {
        pair<int, int> p = split(root, v - 1);
        pair<int, int> p1 = split(p.second, 1);
        int before = end(p.first), after = begin(p1.second);
        nalog -= len(p1.first);
        free.push_back(p1.first);
        if (before == -1) {
            nalog -= len(after);
            d[after]->add(d[p1.first]->s, d[p1.first]->f);
            nalog += len(after);
        } else if (after == -1) {
            nalog -= len(before);
            d[before]->add(d[p1.first]->s, d[p1.first]->f);
            nalog += len(before);
        } else {
            int mid = (d[p1.first]->s + d[p1.first]->f) >> 1;
            nalog -= len(before);
            d[before]->add(d[p1.first]->s, mid);
            nalog += len(before);
            nalog -= len(after);
            d[after]->add(mid, d[p1.first]->f);
            nalog += len(after);
        }
        root = merge(p.first, p1.second);
    }

    void divide(int v) {
        pair<int, int> p = split(root, v - 1);
        pair<int, int> p1 = split(p.second, 1);
        nalog -= len(p1.first);
        int mid = (d[p1.first]->s + d[p1.first]->f) >> 1;
        int u = new_v(mid, d[p1.first]->f);
        d[p1.first]->f = mid;
        nalog += len(p1.first);
        nalog += len(u);
        root = merge(p.first, merge(p1.first, merge(u, p1.second)));
    }

    int add_back(int l, int last_l) {
        int v = new_v(last_l, last_l + l);
        nalog += len(v);
        root = merge(root, v);
        return last_l + l;
    }

    void print_decart() {
        print(root);
        cout << endl;
    }

    void print(int v) {
        if (v == -1) {
            return;
        }
        if (d[v]->l != -1) {
           print(d[v]->l);
        }
        cout << d[v]->s << "<->" << d[v]->f << "  ";
        if (d[v]->r != -1) {
            print(d[v]->r);
        }
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, p, last = 0;
    cin >> n >> p;
    decart d;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        last = d.add_back(t, last);
    }
    cout << d.nalog << '\n';
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            d.rip(v);
        } else if (type == 2) {
            d.divide(v);
        }
        //d.print_decart();
        cout << d.nalog << '\n';
    }
    return 0;
}
