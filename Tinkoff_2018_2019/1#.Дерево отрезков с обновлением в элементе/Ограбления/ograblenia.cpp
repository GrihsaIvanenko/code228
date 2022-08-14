#include <bits/stdc++.h>

using namespace std;

struct segtree {
    int lb, rb;
    long long l_ = 0, r_ = 0, max_, min_ = 0;
    segtree *l = 0, *r = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void update(){
        if(lb + 1 == rb)return;
        l_ = max(l->l_ + r->l_, l->min_ + r->max_);
        r_ = max(l->r_ + r->r_, r->min_ + l->max_);
        max_ = max(l->max_ + r->l_, l->r_ + r->max_);
        min_ = max(l->min_ + r->r_, r->min_ + l->l_);
    }
    void change(int pos, int mean){
        if(lb + 1 == rb){
            max_ = mean;
            return;
        }
        if(pos < (lb + rb) / 2){
            l->change(pos, mean);
        }
        else{
            r->change(pos, mean);
        }
        update();
    }
    void ccc(){
        if(lb + 1 == rb){
            cout<<lb<<" "<<rb<<" "<<min_<<" "<<l_<<" "<<r_<<" "<<max_<<endl;
            return;
        }
        l->ccc();
        r->ccc();
        cout<<lb<<" "<<rb<<" "<<min_<<" "<<l_<<" "<<r_<<" "<<max_<<endl;
    }
};

int f(int x){
    if(x == 1){
        return x;
    }
    return f((x+1)>>1)<<1;
}

int main(){
    int n, m;
    cin >> n >> m;
    segtree *t = new segtree(0, f(n));
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        t->change(i, x);
    }
    cout << t->max_ << endl;
    for(int i = 0; i < m; ++i){
        int p, x;
        cin >> p >> x;
        p--;
        t->change(p, x);
        cout << t->max_ << endl;
       // t->ccc();
        //cout << endl;
    }
    return 0;
}


