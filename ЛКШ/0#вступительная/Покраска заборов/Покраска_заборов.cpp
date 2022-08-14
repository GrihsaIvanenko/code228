#include <bits/stdc++.h>

using namespace std;

struct segtree {
    int lb, rb;
    bool push = 0;
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
        if(rb - lb == 1)
            return;
        l->push = push;
        r->push = push;
    }
    bool chec(int x){
        update();
        if(rb - lb == 1)
            return push;
        int mid = (lb + rb)>>1;
        if(x >= mid)
            return r->chec(x);
        else l->chec(x);
    }
    void push_segment(int l, int r, bool mean){
        if(r < l)return;
        if(l >= rb || r <= lb)
            return;
        if(l >= lb && r <= rb){
            push = mean;
            return;
        }
        int mid = (lb + rb)>>1;
        push_segment(lb, mid, mean);
        push_segment(mid, rb, mean);
    }
};

signed main(){
    segtree d_o(0, 1024 * 1024);
    int n, ans = 0;
    cin >> n;
    int act[n];
    vector<pair<pair<pair<int, int>, bool>,pair<int,int>>> open;
    for(int i = 0; i < n; ++i){
        act[i] = 0;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        open.push_back({ {{x1, i}, 0}, {y1, y2} });
        open.push_back({ {{x2, i}, 1}, {y1, y2} });
    }
    sort(open.begin(), open.end());
    for(int i = 0; i < open.size(); ++i){
        pair<pair<pair<int, int>, bool>,pair<int,int>> p = open[i];
        if(p.first.second == 1){
            if(act[p.first.first.second]){
                d_o.push_segment(p.second.first, p.second.second, 0);
            }
        }
        else{
            if(d_o.chec(p.second.first) == 0){
                ++ans;
                act[p.first.first.second] = 1;
                d_o.push_segment(p.second.first, p.second.second, 1);
            }
        }
    }
    cout << ans << endl;
    return 0;
}

