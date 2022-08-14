#include <bits/stdc++.h>

using namespace std;

struct segtree{
    int lb, rb, val, push;
    segtree *l = nullptr, *r = nullptr;
    segtree(int lb_, int rb_){
        lb = lb_;
        rb = rb_;
        val = rb - lb_;
        push = 2;
    }
    void update(){
        if(push == 2){
            val = 0;
            if(l != nullptr){
                if(l->push == 2){
                    val += l->val;
                }
                else{
                    val += ((rb - lb)>>1) * l->push;
                }
            }
            else{
                val += ((rb - lb)>>1);
            }
            if(r != nullptr){
                if(r->push == 2){
                    val += r->val;
                }
                else{
                    val += ((rb - lb)>>1) * r->push;
                }
            }
            else{
                val += (rb - lb)>>1;
            }
        }
        else{
            if(push == 1){
                if(l != nullptr){
                    l->push = push;
                }
                if(r != nullptr){
                    r->push = push;
                }
            }
            else{
                if(l == nullptr){
                    l = new segtree(lb, (lb + rb)>>1);
                }
                if(r == nullptr){
                    r = new segtree((lb + rb)>>1, rb);
                }
                l->push = push;
                r->push = push;
            }
            val = (rb - lb) * push;
            push = 2;
        }
    }
    void plus_(int le, int re, int t){
        if(le >= rb || re <= lb){
            return;
        }
        update();
        if(le <= lb && rb <= re){
            push = t;
            return;
        }
        if(le >= ((lb + rb)>>1)){
            if(r == nullptr){
                r = new segtree((lb + rb)>>1, rb);
            }
            r->plus_(le, re, t);
            update();
        }
        else if(re <= ((lb + rb)>>1)){
            if(l == nullptr){
                l = new segtree(lb, (lb + rb)>>1);
            }
            l->plus_(le, re, t);
            update();
        }
        else{
            if(l == nullptr){
                l = new segtree(lb, (lb + rb)>>1);
            }
            if(r == nullptr){
                r = new segtree((lb + rb)>>1, rb);
            }
            l->plus_(le, re, t);
            r->plus_(le, re, t);
            update();
        }
    }
    void print(){
        cout << lb << " " << rb << " - " << val << " " << push << endl;
        if(l == nullptr){
            cout << lb << " " << rb << " no L\n";
        }
        else{
            l->print();
        }
        if(r == nullptr){
            cout << lb << " " << rb << " no R\n";
        }
        else{
            r->print();
        }
    }
};

const int MAXN = 1073741824;

int main(){
    segtree *x = new segtree(0, MAXN);
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int l, r, q;
        cin >> l >> r >> q;
        x->plus_(l - 1, r, q - 1);
        //x->print();
        cout << x->val - MAXN + n << '\n';
    }
    return 0;
}
