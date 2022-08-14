#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

struct Node{
    int x, y, l, r;
    bool del;
    Node(int x_) {
        x = x_;
        y = rand();
        l = -1;
        r = - 1;
    }
};

struct my_set{
    vector<Node*> d;
    vector<int> free;
    int root = -1;

    int begin(int v) {
        if (v == -1) {
           return -INF;
        }
        if (d[v]->l == -1) {
           return d[v]->x;
        }
        return begin(d[v]->l);
    }

    int end(int v) {
        if (v == -1) {
            return -INF;
        }
        if (d[v]->r == -1) {
            return d[v]->x;
        }
        return end(d[v]->r);
    }

    pair<int, int> split(int v, int x) {
        if (v == -1) {
           return {-1, -1};
        }
        pair<int, int> p;
        if (d[v]->x < x) {
            p = split(d[v]->r, x);
            d[v]->r = p.first;
            return {v, p.second};
        } else {
            p = split(d[v]->l, x);
            d[v]->l = p.second;
            return {p.first, v};
        }
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
           return v;
        } else {
            d[u]->l = merge(v, d[u]->l);
            return u;
        }
    }

    void insert(int x) {
        pair<int, int> p = split(root, x);
        pair<int, int> p1 = split(p.second, x + 1);
        if (p1.first != -1) {
            root = merge(p.first, merge(p1.first, p1.second));
            return;
        }
        int id;
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

    void delet(int x) {
        pair<int, int> p = split(root, x);
        pair<int, int> p1 = split(p.second, x + 1);
        if (p1.first != -1) {
           free.push_back(p1.first);
        }
        root = merge(p.first, p1.second);
    }

    bool exists(int x) {
        pair<int, int> p = split(root, x);
        pair<int, int> p1 = split(p.second, x + 1);
        bool res = p1.first != -1;
        root = merge(p.first, merge(p1.first, p1.second));
        return res;
    }

    int next(int x) {
        pair<int, int> p = split(root, x + 1);
        int res = begin(p.second);
        root = merge(p.first, p.second);
        return res;
    }

    int prev(int x) {
        pair<int, int> p = split(root, x);
        int res = end(p.first);
        root = merge(p.first, p.second);
        return res;
    }

    void print(int v) {
        if (v == -1) {
           return;
        }
        print(d[v]->l);
        cout << v << ": " << d[v]->x << " " << d[v]->l << " " << d[v]->r << endl;
        print(d[v]->r);
    }
};

int main(){
    string str;
    int tmp;
    my_set s;
    while(cin >> str >> tmp) {
        if (str == "insert") {
           s.insert(tmp);
        } else if(str == "delete") {
            s.delet(tmp);
        } else if(str == "exists") {
            bool res = s.exists(tmp);
            if (res) {
               cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (str == "next") {
            int res = s.next(tmp);
            if (res == -INF) {
                cout << "none\n";
            } else {
                cout << res << '\n';
            }
        } else if (str == "prev") {
            int res = s.prev(tmp);
            if (res == -INF) {
                cout << "none\n";
            } else {
                cout << res << '\n';
            }
        }
    }
    return 0;
}
