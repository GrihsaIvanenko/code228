#include <bits/stdc++.h>

using namespace std;

int last_r = 0;

struct segtree {
    int lb, rb, left, right, mean, max_l;
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
            update();
            return;
        }
        int t = (lb + rb) / 2;
        if(pos < t){
            if(!l){
               l = new segtree(lb, t);
            }
            l->build(pos, x);
        }
        else{
            if(!r){
               l = new segtree(t, rb);
            }
            r->build(pos, x);
        }
        update();
    }
    void change(int k, int x){
        if(lb + 1 == rb){
            mean = x;
             update();
            return;
        }
        if (k < l->rb)
            l->change(k, x);
        else
            r->change(k, x);
             update();
    }
    void update(){
        if(lb + 1 == rb){
            if(mean == 0){
                max_l = left = right = 1;
            }
            else{
                max_l = left = right = 0;
            }
        }
        else{
            max_l = max(l->max_l, max(r->max_l, l->right + r->left));
            left = l->left;
            if(l->left == l->rb - l->lb){
                left += r->left;
            }
            right = r->right;
            if(r->right == r->rb - r->lb){
                right += l->right;
            }
        }
    }
    void ccc(){
        cout << left << " " << right << " " << max_l << " " << lb << " " << rb << endl;
        if(l){
            l->ccc();
        }
        if(r){
            r->ccc();
        }
    }
    int makeans(int le, int re){
        if(lb >= re || rb <= le){
            //cout << lb << " " << rb << " return" << endl;
            return 0;
        }
        //cout << lb << " " << rb << endl;
        if(lb >= le && rb <= re){
            int ans = max(left + last_r, max_l);
            if(right == rb - lb){
                last_r += right;
            }
            else{
                last_r = right;
            }
           // cout << lb << " " << rb << endl;
            return ans;
        }
        //return max(l->makeans(le,re), r->makeans(le,re));
        int ans = l->makeans(le,re);
        int ans1 = r->makeans(le, re);
        return max(ans, ans1);
    }
};

int f(int n){
    if(n == 1){
        return n;
    }
    return f((n + 1) / 2) * 2;
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    segtree *x = new segtree(0, n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
        x->build(i, min(1,v[i]));
    }
    cin >> n;
    for(int i = 0; i < n; ++i){
        string s;
        int a, b;
        cin >> s >> a >> b;
        a--;
        if(s[0] == 'Q'){
            last_r = 0;
            int hrjjc = x->makeans(a, b);
            cout << hrjjc << endl;
        }
        if(s[0] == 'U'){
            x->change(a, min(1,b));
        }
        //x->ccc();
    }
    return 0;
}

