#include <bits/stdc++.h>

using namespace std;

vector<pair<pair<long long, long long>, int>> lef, righ;

struct segtree{
    segtree *l, *r;
    int lb, mid, rb, pos;
    long long val;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        val = -1;
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void update() {
        if (l->val > r->val) {
            val = l->val;
            pos = l->pos;
        } else{
            val = r->val;
            pos = r->pos;
        }
    }
    void adde(int pose, long long it) {
        if (rb - lb == 1) {
            val = it;
            pos = pose;
            return;
        }
        if (pose < mid) {
            l->adde(pose, it);
        } else{
            r->adde(pose, it);
        }
        update();
    }
    pair<int, long long> max_(int le, int re) {
        if (le >= rb || re <= lb) {
            return {-1, -1};
        }
        if (le <= lb && rb <= re) {
            return {pos, val};
        }
        pair<int, long long> lele = l->max_(le, re), rere = r->max_(le, re);
        if (lele.second > rere.second) {
            return lele;
        }
        return rere;
    }
    void print() {
        cout << lb << " " << rb << " : " << val << " " << pos << endl;
        if (rb - lb != 1) {
            l->print();
            r->print();
        }
    }
};

void solve() {
    int n;
    long long L, R;
    cin >> n >> L >> R;
    vector<pair<long long, long long>> v1, v2;
    for (int i = 0; i < (n >> 1); ++i) {
        long long a, b;
        cin >> a >> b;
        v1.push_back({a, b});
    }
    lef.resize(1 << v1.size());
    for (int i = (n >> 1); i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        v2.push_back({a, b});
    }
    righ.resize(1 << v2.size());
    for (int i = 0; i < (1 << v1.size()); ++i) {
        lef[i].second = i;
        for (int j = 0; j < v1.size(); ++j) {
            if ((1 << j) & i) {
                lef[i].first.first += v1[j].first;
                lef[i].first.second += v1[j].second;
            }
        }
    }
    for (int i = 0; i < (1 << v2.size()); ++i) {
        righ[i].second = i;
        for (int j = 0; j < v2.size(); ++j) {
            if ((1 << j) & i) {
                righ[i].first.first += v2[j].first;
                righ[i].first.second += v2[j].second;
            }
        }
    }
    sort (lef.begin(), lef.end());
    sort (righ.begin(), righ.end());
    /*cout << "Left\n";
    for (int i = 0; i < lef.size(); ++i) {
        cout << i << " " << lef[i].first << " " << lef[i].second << endl;
    }
    cout << "Righ\n";
    for (int i = 0; i < righ.size(); ++i) {
        cout << i << " " << righ[i].first << " " << righ[i].second << endl;
    }
    cout << endl;*/
    segtree *z = new segtree(0, righ.size());
    for (int i = 0; i < righ.size(); ++i) {
        z->adde(i, righ[i].first.second);
    }
    //z->print();
    int a = -1, b = -1;
    vector<long long> rcopy;
    for (auto x : righ) {
        rcopy.push_back(x.first.first);
    }
    for (int i = 0; i < lef.size(); ++i) {
        int l = (lower_bound(rcopy.begin(), rcopy.end(), (L - lef[i].first.first)) - rcopy.begin());
        int r = (upper_bound(rcopy.begin(), rcopy.end(), (R - lef[i].first.first)) - rcopy.begin());
        //cout  << i << " " << lef[i].first << " " << l << " " << r << endl;
        if (l >= r) {
            continue;
        } else if (a == -1 || z->max_(l, r).second + lef[i].first.second > lef[a].first.second + righ[b].first.second){
            a = i;
            b = z->max_(l, r).first;
        }
    }
    if (a == -1) {
        cout << "0\n";
        return;
    }
    a = lef[a].second;
    b = righ[b].second;
    vector<int> ans;
    for (int i = 0; i < v1.size(); ++i) {
        if (a & (1 << i)) {
            ans.push_back(i + 1);
        }
    }
    for (int i = 0; i < v2.size(); ++i) {
        if (b & (1 << i)) {
            ans.push_back(i + v1.size() + 1);
        }
    }
    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x << " ";
    }
}

signed main() {
    solve();
    return 0;
}
