#include <bits/stdc++.h>

using namespace std;

const int MAXN = 262144;

const long long INF = 1e13;

struct segtree{
    int lb, rb, mid;
    long long val, push;
    segtree *l = nullptr, *r = nullptr;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        val = INF;
        push = 0;
        if (lb + 1 != rb) {
           l = new segtree(lb, mid);
           r = new segtree(mid, rb);
        }
    }
    void add(int pos, long long ch) {
        if(lb + 1 == rb) {
            val = ch;
            return;
        }
        if (pos < mid) {
           l->add(pos, ch);
        } else {
            r->add(pos, ch);
        }
        update();
    }
    void update() {
        if (push == 0) {
            if (lb + 1 == rb) {
                return;
            }
            val = min(l->val + l->push, r->val + r->push);
            return;
        }
        if (lb + 1 == rb) {
           val += push;
           push = 0;
           return;
        }
        l->push += push;
        r->push += push;
        push = 0;
        val = min(l->val + l->push, r->val + r->push);
    }
    void inc(int le, int re, long long in) {
        if (le >= rb || lb >= re) {
            return;
        }
        if (le <= lb && rb <= re) {
            push += in;
            return;
        }
        l->inc(le, re, in);
        r->inc(le, re, in);
        update();
    }
    long long rmq(int le, int re) {
        if (le >= rb || lb >= re) {
            return INF;
        }
        update();
        if (le <= lb && rb <= re) {
            return val;
        }
        return min(l->rmq(le, re) + l->push, r->rmq(le, re) + r->push);
    }
    void print() {
        cout << lb << " " << rb << ": " << val << " " << push << endl;
        if(l) {
            l->print();
            r->print();
        }
    }
};

int main(){
    segtree *root = new segtree(0, MAXN);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        root->add(i, t);
    }
    int m;
    cin >> m;
    if(m == 0) {
        return 0;
    }
    string s;
    getline(cin, s);
    for (int i = 0; i < m; ++i) {
        s.clear();
        getline(cin, s);
        s.push_back('$');
        int lef = 0, righ = 0;
        int it = 0;
        while (s[it] >= '0' && s[it] <= '9') {
            lef *= 10;
            lef += (int)(s[it++] - '0');
        }
        ++it;
        while (s[it] >= '0' && s[it] <= '9') {
            righ *= 10;
            righ += (int)(s[it++] - '0');
        }
        if (s[it] == '$') {
            if (lef <= righ) {
                cout << root->rmq(lef, righ + 1)<< endl;
            } else {
                cout << min(root->rmq(0, righ + 1), root->rmq(lef, n)) << endl;
            }
        } else {
            long long incr = 0;
            ++it;
            bool minu = false;
            if (s[it] == '-') {
               minu = true;
               ++it;
            }
            while (s[it] != '$') {
                incr *= 10ll;
                incr += (long long)(s[it++] - '0');
            }
            if(minu) {
                incr = -incr;
            }
            if (lef <= righ) {
                root->inc(lef, righ + 1, incr);
            } else {
                root->inc(0, righ + 1, incr);
                root->inc(lef, n, incr);
            }
        }
    }
    return 0;
}


