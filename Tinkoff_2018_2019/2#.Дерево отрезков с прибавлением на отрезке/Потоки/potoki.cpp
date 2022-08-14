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
    /*
    void plus_(int lq, int rq, int x){
        if(lq >= rb || rq <= lb){
            return;
        }
        update();
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
    }*/
    bool look(int lq, int rq, int k){
        if(lq >= rb || rq <= lb){
            return true;
        }
        update();
        if(lq <= lb && rb <= rq){
            return mean < k;
        }
        return l->look(lq, rq, k) && r->look(lq, rq, k);
    }
     void plus_(int lq, int rq){
        if(lq >= rb || rq <= lb){
            return;
        }
        update();
        if(lq <= lb && rb <= rq){
            ++push;
            return;
        }
        l->plus_(lq, rq);
        r->plus_(lq, rq);
        update();
    }
};

int f(int n){
    if(n == 1){
        return 1;
    }
    return f((n + 1) / 2) * 2;
}

int main(){
    int n, k;
    cin >> n >> k;
    segtree kek(0, f(n));
    for(int i = 0; i < n; ++i){
        kek.build(i, 0);
    }
    cin >> n;
    for(int i = 0; i < n; ++i){
        int a, b;
        cin >> a >> b;
        if(kek.look(a, b, k)){
            cout << 1 << endl;
            kek.plus_(a, b);
        }
        else{
            cout << 0 << endl;
        }
    }
}
