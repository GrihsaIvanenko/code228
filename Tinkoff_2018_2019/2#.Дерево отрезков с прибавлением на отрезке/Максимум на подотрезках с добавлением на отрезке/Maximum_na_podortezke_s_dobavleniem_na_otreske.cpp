#include <bits/stdc++.h>

using namespace std;

int se = 2;

struct segtree {
    int lb, rb, mean = 0, push = 0;
    segtree *l = 0, *r = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void build(int pos, int x){
        if(lb + 1 == rb){
            mean = x;
            return;
        }
        int t = (lb+ rb) / 2;
        if(pos < t){
            if(!l){
                l = new segtree(lb, t);
            }
            l->build(pos, x);
        }
        else{
            if(!r){
                r = new segtree(t, rb);
            }
            r->build(pos, x);
        }
        update();
    }
    void update(){
        if(lb + 1 == rb){
            mean += push;
            push = 0;
            return;
        }
        mean = max(l->mean + l->push, r->mean + r->push) + push;
        l->push += push;
        r->push += push;
        push = 0;
    }
    void plus_(int lq, int rq, int x){
        if(lq >= rb || rq <= lb){
            return;
        }
        if(lq <= lb && rb <= rq){
            push += x;
            return;
        }
        l->plus_(lq, rq, x);
        r->plus_(lq, rq, x);
        update();
    }
    int ans(int lq, int rq){
        if(lq >= rb || rq <= lb){
            return -1;
        }
       update();
        if(lq <= lb && rb <= rq){
            return mean;
        }
        return max(l->ans(lq, rq), r->ans(lq, rq));
    }
     void ccc(){
        cout << mean << " " << push << " " << lb << " " << rb << endl;
        if(l){
            l->ccc();
        }
        if(r){
            r->ccc();
        }
    }
};

int f(int n){
    if(n == 1){
        return 1;
    }
    return f((n + 1) / 2) * 2;
}

int main(){
    int n;
    cin >> n;
    //cout << f(n) << endl;
    segtree kek(0, f(n));
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        kek.build(i, x);
    }
    cin >> n;
    for(int i = 0; i < n; ++i){
        char f;
        cin >> f;
        if(f == 'm'){
            int pos, pos1;
            cin >> pos >> pos1;
            cout << kek.ans(pos - 1, pos1) << " ";
        }
        else{
            int a, b, c;
            cin >> a >> b >> c;
            kek.plus_(a - 1, b, c);
        }
        //kek.ccc();
    }
}
