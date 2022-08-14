#include <bits/stdc++.h>

using namespace std;

struct segtree{
    segtree *l = 0, *r = 0;
    int lb, rb, midb, sum;
    bitset<1000> jkaf;
    segtree(int _lb, int _rb) {
        lb = _lb;
        rb = _rb;
        midb = (lb + rb)>>1;
        sum = 0;
    }
    void update(){
        if(l != 0 && r != 0)
            sum = l->sum + r->sum;
        else if(l == 0 && r != 0)
            sum = r->sum;
        else if(l != 0)
            sum = l->sum;
        else
            sum = 0;
    }
    void build(){
        if (lb + 1 < rb) {
            l = new segtree(lb, midb);
            r = new segtree(midb, rb);
            l->build();
            r->build();
        }
    }
};


int m;

segtree *cop(segtree *id){
    segtree *ideal = new segtree(id->lb, id->rb);
    ideal->jkaf = id->jkaf;
    ideal->sum = id->sum;
    return ideal;
}
segtree *copyy(segtree id){
    segtree *ideal = new segtree(id.lb, id.rb);
    ideal->l = id.l;
    ideal->r = id.r;
    ideal->jkaf = id.jkaf;
    ideal->sum = id.sum;
    return ideal;
}

segtree *make_operation(int a, int b, int c, segtree *id){
    segtree *it = cop(id);
    if(it->rb - it->lb > 1){
        if(b >= it->midb){
            it->l = id->l;
            it->r = make_operation(a, b, c, id->r);
        }
        else{
            it->r = id->r;
            it->l = make_operation(a, b, c, id->l);
        }
        it->update();
    }
    else{
        it->jkaf = id->jkaf;
        it->sum = id->sum;
        if(a == 1){
            if(it->jkaf[c] == 0){
                it->jkaf[c] = 1;
                it->sum++;
            }
        }
        else if(a == 2){
            if(it->jkaf[c] == 1){
                it->jkaf[c] = 0;
                it->sum--;
            }
        }
        else if(a == 3){
            it->jkaf.flip();
            it->sum = 0;
            for(int i = 0; i < m; ++i)
                it->sum += it->jkaf[i];
        }
    }
    return it;
}

void solve(){
    segtree *start = new segtree(0, 1024);
    start->build();
    vector<segtree> root = {*start};
    int n, q;
    cin >> n >> m >> q;
    for(int i = 0; i < q; ++i){
        int a, b, c = 0;
        cin >> a >> b;
        --b;
        if(a < 3){
            cin >> c;
            --c;
        }
        if(a == 4)
            root.push_back(root[b + 1]);
        else{
            segtree *it = copyy(root.back());
            root.push_back(*make_operation(a, b, c, it));
        }
        cout << root.back().sum << '\n';
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
