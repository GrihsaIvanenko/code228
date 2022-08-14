#include <bits/stdc++.h>

using namespace std;

struct segtree{
    int lb, rb, mid, sum;
    segtree *l = nullptr, *r = nullptr;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        sum = 0;
    }
    void first_build(){
        if (rb - lb != 1){
            l = new segtree(lb, mid);
            l->first_build();
            r = new segtree(mid, rb);
            r->first_build();
        }
    }
    void add(segtree *ideal, int pos){
        if (rb - lb == 1){
            l = nullptr;
            r = nullptr;
            sum = ideal->sum + 1;
            return;
        }
        if (pos < ideal->mid){
            r = ideal->r;
            l = new segtree(lb, mid);
            l->add(ideal->l, pos);
        }
        else{
            l = ideal->l;
            r = new segtree(mid, rb);
            r->add(ideal->r, pos);
        }
        sum = l->sum + r->sum;
    }
    long long pos(segtree *le, int k){
        if (rb - lb == 1){
            return lb;
        }
        if (l->sum - le->l->sum < k){
            return r->pos(le->r, k + le->l->sum - l->sum);
        }
        return l->pos(le->l, k);
    }
};

void solve(){
    long long n;
    cin >> n;
    long long sz = 1;
    while (sz < n){
        sz = sz << 1;
    }
    segtree *null_do = new segtree(0, sz);
    null_do->first_build();
    vector<segtree*> roots;
    roots.push_back(null_do);
    vector<int> vals, val_mem;
    map<int, int> compress;
    int  a1, l, m, mod = 1e9;
    cin >> a1 >> l >> m;
    vals.push_back(a1);
    val_mem.push_back(vals.back());
    for (int i = 1; i < n; ++i){
        vals.push_back((long long)(vals.back() * (long long)l + (long long)m) % mod);
        val_mem.push_back(vals.back());
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < vals.size(); ++i){
        compress[vals[i]] = i;
    }
    for (int i = 0; i < n; ++i){
        segtree *newroot = new segtree(0, sz);
        newroot->add(roots.back(), compress[val_mem[i]]);
        roots.push_back(newroot);
    }
    int B;
    cin >> B;
    long long  ans = 0;
    for (int ch = 0; ch < B; ++ch){
        long long G, x1, lx, mx, y1, ly, my, k1, lk, mk, xg, yg, ig, jg, kg;
        cin >> G >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        xg = x1;
        yg = y1;
        ig = min(x1, y1);
        jg = max(x1, y1);
        kg = k1;
        ans += vals[roots[jg]->pos(roots[ig - 1], kg)];
        for (int i = 1; i < G; ++i){
            xg = ((ig - 1) * lx + mx) % n + 1;
            yg = ((jg - 1) * ly + my) % n + 1;
            ig = min(xg, yg);
            jg = max(xg, yg);
            kg = (((kg - 1) * lk + mk) % (jg - ig + 1)) + 1;
            ans += vals[roots[jg]->pos(roots[ig - 1], kg)];
        }
    }
    cout << ans << endl;
}

int main(){
    solve();
    return 0;
}
