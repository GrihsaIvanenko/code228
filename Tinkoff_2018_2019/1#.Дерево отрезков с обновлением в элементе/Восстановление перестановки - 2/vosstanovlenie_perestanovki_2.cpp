#include <bits/stdc++.h>

using namespace std;

struct segtree{
    int lb, rb, sum;
    segtree *l = 0, *r = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb, sum = 0;
        if (lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void change(int pos, int x){
        if(lb + 1 == rb){
            sum = x;
            return;
        }
        if(pos <(lb + rb) / 2){
            l->change(pos, x);
        }
        else{
            r->change(pos, x);
        }
        sum = l->sum + r->sum;
    }
    int get(int what){
        if(lb + 1 == rb){
            return lb;
        }
        if(r->sum >= what){
            return r->get(what);
        }
        else{
            return l->get(what - r->sum);
        }
    }
    void ccc(){
    cout << lb << " " << rb << " " << sum << endl;
    if(lb + 1 != rb){
        l->ccc();
        r->ccc();
    }
    }
};

int f(int n){
    if(n == 1)return n;
    return f((n + 1)>>1)<<1;
}

int main(){
    int n;
    cin >> n;
    segtree *x = new segtree(0, f(n));
    vector<int> v(n), ans(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
        x->change(i, 1);
    }
    //x->ccc();
    //cout << endl;
    for(int i = n - 1; i > -1; --i){
        int pos = x->get(v[i] + 1);
        v[i] = pos;
        x->change(pos, 0);
        //x->ccc();
        //cout << endl;
    }
    for(int i = 0; i < n; ++i){
        cout << v[i] + 1 << " ";
    }
    return 0;
}
