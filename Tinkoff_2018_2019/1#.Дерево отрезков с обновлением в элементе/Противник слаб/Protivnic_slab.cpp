#include <bits/stdc++.h>

using namespace std;

struct segtree{
    int lb, rb;
    long long sum, sum1;
    segtree *l = 0, *r = 0;
    segtree(long long _lb, long long _rb){
        lb = _lb, rb = _rb, sum1 = sum = 0;
    }
    void change(int pos, long long x){
        if(lb + 1 == rb){
            sum = x;
            return;
        }
        if(pos <(lb + rb) / 2){
            if(!l){
                l = new segtree(lb, (lb + rb) / 2);
            }
            l->change(pos, x);
        }
        else{
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            r->change(pos, x);
        }
        sum = 0;
        if(l){
            sum = l->sum;
        }
        if(r){
            sum += r->sum;
        }
    }
    void change1(int pos, long long x){
        if(lb + 1 == rb){
            sum1 = x;
            return;
        }
        if(pos <(lb + rb) / 2){
            if(!l){
                l = new segtree(lb, (lb + rb) / 2);
            }
            l->change1(pos, x);
        }
        else{
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            r->change1(pos, x);
        }
        sum1 = 0;
        if(l){
            sum1 = l->sum1;
        }
        if(r){
            sum1 += r->sum1;
        }
    }
    long long get(int what){
        if(lb + 1 == rb){
            return 0;
        }
        if((lb + rb) / 2 > what){
            if(!l){
                l = new segtree(lb, (lb + rb) / 2);
            }
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            return l->get(what) + r->sum;
        }
        else{
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            return r->get(what);
        }
    }
    long long get1(int what){
        if(lb + 1 == rb){
            return 0;
        }
        if((lb + rb) / 2 > what){
            if(!l){
                l = new segtree(lb, (lb + rb) / 2);
            }
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            return l->get1(what) + r->sum1;
        }
        else{
            if(!r){
                r = new segtree((lb + rb) / 2, rb);
            }
            return r->get1(what);
        }
    }
};

int f( int n){
    if(n == 1)
        return n;
    return f((n + 1)>>1)<<1;
}

int main(){
    int n;
    cin >> n;
    int d = n;
    unsigned long long ans = 0;
    vector<int> means(n), v1(n);
    for(int i = 0; i < n; ++i){
        cin >> means[i];
        v1[i] = means[i];
    }
    sort(v1.begin(), v1.end());
    map<int,int>mm;
    for(int i = 0; i < n; ++i){
        mm[v1[i]] = i;
    }
    v1.clear();
    for(int i = 0; i < n; ++i){
        means[i] = mm[means[i]];
    }
    mm.clear();
    segtree *x = new segtree(0, f(d));
    for(int i = 0; i < n; ++i){
        long long mean = x->get(means[i]);
        x->change(means[i], 1);
        ans += x->get1(means[i]);
        x->change1(means[i], mean);
    }
    cout << ans;
    return 0;
}
