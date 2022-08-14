#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pow popo

const long long mod = 1e9+7, K = 100003;

const int MAXN = 131072;

long long pow[MAXN], pref_sum[MAXN];

struct segtree{
    int lb, rb, mid;
    long long has = 0, push = 0;
    segtree *l = 0, *r = 0;
    segtree(int lb_, int rb_){
        lb = lb_;
        rb = rb_;
        mid = (lb + rb)>>1;
        if(lb + 1 != rb){
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void update(){
        if(push == 0){
            if(lb + 1 == rb)
                return;
            long long l_hash = 0, r_hash = 0;
            if(l->push == 0){
                l_hash = l->has;
            }
            else{
                l_hash = (pref_sum[mid - lb - 1] * l->push) % mod;
            }
            if(r->push == 0){
                r_hash = r->has;
            }
            else{
                r_hash = (pref_sum[rb - mid - 1] * r->push) % mod;
            }
            has = ((l_hash * pow[mid - lb]) % mod + r_hash) % mod;
            return;
        }
        if(lb + 1 == rb){
            has = push;
            push = 0;
            return;
        }
        l->push = push;
        r->push = push;
        has = (pref_sum[rb - lb - 1] * push) % mod;
        push = 0;
        return;
    }
    void place(int pos, int col){
        if(lb + 1 == rb){
            has = col;
            return;
        }
        if(mid > pos){
            l->place(pos, col);
        }
        else{
            r->place(pos, col);
        }
        update();
    }
    void color(int le, int re, int col){
        if(le >= rb || re <= lb){
            return;
        }
        update();
        if(le <= lb && rb <= re){
            push = col;
            update();
            return;
        }
        l->color(le, re, col);
        r->color(le, re, col);
        update();
    }
    long long get_hash(int le, int re){
        update();
       if(le <= lb && rb <= re){
           return has;
        }
        if(re <= mid){
            return l->get_hash(le, re);
        }
        if(le >= mid){
            return r->get_hash(le, re);
        }
        return ((l->get_hash(le, mid) * pow[re - mid]) % mod + r->get_hash(mid, re)) % mod;
    }
    void print_me(){
        cout << lb << " " << mid << " " << rb << " " << push << " " << has << endl;
        if(l != 0)
            l->print_me();
        if(r != 0)
            r->print_me();
    }
};

void calc(){
    pow[0] = pref_sum[0] = 1;
    for(int i = 1; i < MAXN; ++i){
        pow[i] = (pow[i - 1] * K) % mod;
        pref_sum[i] = (pref_sum[i - 1] + pow[i]) % mod;
    }
}

int n, m;

vector<int> v;

vector<pair<pair<int,int>, pair<int,int>>> tasks;

void read(){
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }
    cin >> m;
    tasks.resize(m);
    for(int i = 0; i < m; ++i){
        cin >> tasks[i].x.x >> tasks[i].x.y >> tasks[i].y.x >> tasks[i].y.y;
    }
}

vector<char> ans;

void print_ans(){
    for(auto x : ans){
        cout << x;
    }
    cout << endl;
}

void solve(){
    calc();
    segtree *x = new segtree(0, MAXN);
    for(int i = 0; i < n; ++i){
        x->place(i, v[i]);
    }
    for(int i = 0; i < m; ++i){
        if(tasks[i].x.x == 0){
            x->color(tasks[i].x.y - 1, tasks[i].y.x, tasks[i].y.y);
            //x->print_me();
        }
        else{
            long long a = x->get_hash(tasks[i].x.y - 1, tasks[i].x.y + tasks[i].y.y - 1);
            long long b = x->get_hash(tasks[i].y.x - 1, tasks[i].y.x + tasks[i].y.y - 1);
            if(a == b){
                ans.push_back('+');
            }
            else{
                ans.push_back('-');
            }
        }
    }
}

int main(){
    read();
    solve();
    print_ans();
    return 0;
}
