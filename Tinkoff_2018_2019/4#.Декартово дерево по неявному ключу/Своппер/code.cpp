#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l, r, sz, y;
    long long val, sum;
    Node(int x) {
        val = x;
        y = rand() << 4 + rand();
        sz = 1;
        l = -1;
        r = -1;
        sum = val;
    }
};

vector<Node*> d;

struct decart {
    int root = -1;

    int sz(int v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sz;
    }

    long long sm(int v) {
        if (v == -1) {
           return 0;
        }
        return d[v]->sum;
    }

    void update(int v) {
        if (v == -1) {
           return;
        }
        d[v]->sz = sz(d[v]->l) + 1 + sz(d[v]->r);
        d[v]->sum = sm(d[v]->l) + d[v]->val + sm(d[v]->r);
        return;
    }

    pair<int, int> split(int v, int k) {
        if (v == -1) {
           return {-1, -1};
        }
        if (sz(d[v]->l) >= k) {
           pair<int, int> p = split(d[v]->l, k);
           d[v]->l = p.second;
           update(v);
           return {p.first, v};
        }
        pair<int, int> p = split(d[v]->r, k - 1 - sz(d[v]->l));
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

    void add_back() {
        root = merge(root, d.size() - 1);
    }

    void print() {
        cout << "F: ";
        print_it(root);
        cout << endl;
    }

    void print_it(int v) {
        if (v == -1) {
           return;
        }
        print_it(d[v]->l);
        cout << d[v]->sum << " ";
        print_it(d[v]->r);
    }
};

decart ch, ne;

void swapp(int l, int r) {
   int l_ch = (l - 1) / 2, r_ch = r / 2,
    l_nch = l / 2, r_nc = (r + 1) / 2;
    pair<int, int> pch = ch.split(ch.root, r_ch);
    pair<int, int> p1ch = ch.split(pch.first, l_ch);
    pair<int, int> pne = ne.split(ne.root, r_nc);
    pair<int, int> p1ne = ne.split(pne.first, l_nch);
    ch.root = ch.merge(p1ch.first, ch.merge(p1ne.second, pch.second));
    ne.root = ne.merge(p1ne.first, ne.merge(p1ch.second, pne.second));
}

long long summ(int l, int r) {
    int l_ch = (l - 1) / 2, r_ch = r / 2,
    l_nch = l / 2, r_nc = (r + 1) / 2;
    pair<int, int> pch = ch.split(ch.root, r_ch);
    pair<int, int> p1ch = ch.split(pch.first, l_ch);
    pair<int, int> pne = ne.split(ne.root, r_nc);
    pair<int, int> p1ne = ne.split(pne.first, l_nch);
    long long res = ch.sm(p1ch.second) + ne.sm(p1ne.second);
    ch.root = ch.merge(p1ch.first, ch.merge(p1ch.second, pch.second));
    ne.root = ne.merge(p1ne.first, ne.merge(p1ne.second, pne.second));
    return res;
}

void solve(int &n, int &m, int &i) {
    cout << "Swapper " << i << ":\n";
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        d.push_back(new Node(t));
        if (i % 2) {
            ne.add_back();
        } else {
            ch.add_back();
        }
    }
    for (int i = 0; i < m; ++i) {
        //ch.print();
        //ne.print();
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
           swapp(l, r);
        } else if (t == 2) {
            cout << summ(l, r) << '\n';
        }
    }
    d.clear();
    d.shrink_to_fit();
    ne.root = -1;
    ch.root = -1;
    cout << '\n';
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, i = 1;
    cin >> n >> m;
    while (n != 0 || m != 0) {
        solve(n, m, i);
        cin >> n >> m;
        ++i;
    }
    return 0;
}
