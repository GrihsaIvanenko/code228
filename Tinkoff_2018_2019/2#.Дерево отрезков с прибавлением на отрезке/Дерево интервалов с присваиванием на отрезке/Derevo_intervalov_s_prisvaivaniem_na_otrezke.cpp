#include <bits/stdc++.h>

using namespace std;

struct segtree {
    int lb, rb, push = -1000000000;
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
            push = x;
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
    }
    void pash(){
        if(push == -1000000000)return;
        l->push = push;
        r->push = push;
        push = -1000000000;
    }
    void plus_(int le, int re, int x){

        if(le >= rb || re <= lb){
            return;
        }
        if(lb + 1 == rb){
            push = x;
            return;
        }
        pash();
        if(le <= lb && rb <= re){
            push = x;
            return;
        }
        l->plus_(le, re, x);
        r->plus_(le, re, x);
    }
    int ans(int pos){
        if(push != -1000000000){
            return push;
        }
        int t = (lb + rb) / 2;
        if(pos < t){
            return l->ans(pos);
        }
        return r->ans(pos);
    }
     void ccc(){
        cout << push << " " << lb << " " << rb << endl;
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
        if(f == 'g'){
            int pos;
            cin >> pos;
            cout << kek.ans(pos - 1) << endl;
        }
        else{
            int a, b, c;
            cin >> a >> b >> c;
            kek.plus_(a - 1, b, c);
        }
        //kek.ccc();
    }
}

