#include <bits/stdc++.h>

using namespace std;

struct segtree{
    segtree *l = nullptr, *r = nullptr;
    long long lb, rb, push;
    segtree(long long lb_, long long rb_){
        lb = lb_;
        rb = rb_;
        push = 0;
    }
    void update(){
    if(rb - lb == 1 || push == 0)
        return;
        if(l == nullptr){
            l = new segtree(lb, ((lb + rb)>>1));
        }
        l->push = push;
        if(r == nullptr){
            r = new segtree(((lb + rb)>>1), rb);
        }
        r->push = push;
        push = 0;
    }
    long long check(long long pos){
        if(rb - lb == 1)
            return push;
        if(push != 0)
            return push;
        update();
        if(pos < ((lb + rb)>>1)){
            if(l == nullptr)
                l = new segtree(lb, ((lb + rb)>>1));
            return l->check(pos);
        }
        else{
            if(r == nullptr)
                r = new segtree(((lb + rb)>>1), rb);
            return r->check(pos);
        }

    }
    void plus_(long long ll, long long rl, long long push_){
        if(rl <= lb || ll >= rb){
            return;
        }
        update();
        if(ll <= lb && rl >= rb){
            push = push_;
            return;
        }
        if(l == nullptr)
                l = new segtree(lb, ((lb + rb)>>1));
        l->plus_(ll, rl, push_);
        if(r == nullptr)
                r = new segtree(((lb + rb)>>1), rb);
        r->plus_(ll, rl, push_);
    }
};

int n;

long long w, h;

vector<pair<pair<long long, long long>, int>> trees;

vector<long long> ans;



void solve(){
    sort(trees.begin(), trees.end());
    ans.resize(n);
    segtree *x = new segtree(0, ((1ll)<<42) );
    for(int i = 0; i < n; ++i){
        long long d = x->check(trees[i].first.second);
        d = trees[i].first.first - d;
        ans[trees[i].second] = d;
        x->plus_(trees[i].first.second - d, trees[i].first.second + d, trees[i].first.first + d);
    }
    for(int i = 0; i < n; ++i)
        cout << ans[i]<< '\n';
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> w >> h >> n;
    trees.reserve(n);
    for(int i = 0; i < n; ++i){
        long double a, b;
        cin >> a >> b;
        a *= 2.0000000;
        b *= 2.0000000;
        long long c = a, d = b;
        trees.push_back({{c, d}, i});
    }
    solve();
    return 0;
}
