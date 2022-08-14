#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8;

int n, m, q;

vector<int> input;
vector<pair<int,int>> taskss;

vector<int> ans, ans1;

struct segtree{
    int lb, rb, mid, val = 0;
    segtree *l = nullptr, *r = nullptr;
    segtree() {}
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
    }
    void first_build() {
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            l->first_build();
            r = new segtree(mid, rb);
            r->first_build();
        }
    }
    int sum(int le, int re) {
        if (le == re){
            return 0;
        }
        if (le >= rb || re <= lb) {
            return 0;
        }
        if (le <= lb && rb <= re) {
            return val;
        }
        return l->sum(le, re) + r->sum(le, re);
    }
    void upd(segtree *ideal, int pos, int inc) {
        if (lb + 1 == rb) {
            val = ideal->val + inc;
            return;
        }
        if (pos < mid) {
            r = ideal->r;
            l = new segtree(lb, mid);
            l->upd(ideal->l, pos, inc);
        } else{
            l = ideal->l;
            r = new segtree(mid, rb);
            r->upd(ideal->r, pos, inc);
        }
        val = l->val + r->val;
    }
    void print() {
        cout << lb << " " << rb << " " << val << endl;
        if (rb - lb != 1) {
            l->print();
            r->print();
        }
    }
    int get_pos(int k){
        if (rb - lb == 1){
            return lb;
        }
        if (l->val >= k){
            return l->get_pos(k);
        }
        else{
            return r->get_pos(k - l->val);
        }
    }
};

void solve() {
    vector<vector<int>> inputs(n);
    vector<int> uks(n), data;
    for (int i = 0; i < m; ++i) {
        int t = input[i];
        --t;
        data.push_back(t);
        inputs[t].push_back(i);
    }
    for (int i = 0; i < n; ++i){
        uks[i] = inputs[i].size() - 1;
    }
    vector<segtree*> roots;
    roots.push_back(new segtree(0, MAXN));
    roots.back()->first_build();
    for (int i = 0; i < m; ++i) {
        int it = data[i];
        if (uks[it] == inputs[it].size() - 1) {
            segtree *new_root = new segtree(0, MAXN);
            cout << it << " " << inputs[it][uks[it]] << endl;
            new_root->upd(roots.back(), inputs[it][uks[it]--], 1);
            roots.push_back(new_root);
        } else{
            segtree *new_root = new segtree(0, MAXN);
            new_root->upd(roots.back(), inputs[it][uks[it] + 1], -1);
            segtree *new_new_root = new segtree(0, MAXN);
            new_new_root->upd(new_root, inputs[it][uks[it]--], 1);
            roots.push_back(new_new_root);
        }
    }
    reverse(roots.begin(), roots.end());
    for (int i = 0; i < roots.size(); ++i){
        roots[i]->print();
        cout << endl << endl << endl;
    }
    int p = 0;
    for (int i = 0; i < q; ++i) {
        int a = taskss[i].first, b = taskss[i].second;
        int la = (a + p) % m, ka = (b + p) % n + 1;
        if (roots[la]->sum(la, MAXN) < ka){
            ans.push_back(0);
            p = 0;
        }
        else{
            p = roots[la]->get_pos(ka);
            ans.push_back(++p);
        }
    }
}

void solve1() {
    vector<vector<int>> inputs(n);
    vector<int> uks(n), data;
    for (int i = 0; i < m; ++i) {
        int t = input[i];
        --t;
        data.push_back(t);
        inputs[t].push_back(i);
    }
    vector<segtree*> roots;
    roots.push_back(new segtree(0, MAXN));
    roots.back()->first_build();
    for (int i = 0; i < m; ++i) {
        int it = data[i];
        if (uks[it] == 0) {
            segtree *new_root = new segtree(0, MAXN);
            new_root->upd(roots.back(), inputs[it][uks[it]++], 1);
            roots.push_back(new_root);
        } else{
            segtree *new_root = new segtree(0, MAXN);
            new_root->upd(roots.back(), inputs[it][uks[it] - 1], -1);
            segtree *new_new_root = new segtree(0, MAXN);
            new_new_root->upd(new_root, inputs[it][uks[it]++], 1);
            roots.push_back(new_new_root);
        }
    }
    int p = 0;
    for (int i = 0; i < q; ++i) {
        int a = taskss[i].first, b = taskss[i].second;
        int la = (a + p) % m, ka = (b + p) % n + 1;
        if (roots.back()->sum(la, MAXN) < ka) {
            ans1.push_back(0);
            p = 0;
        } else{
            int l = la, r = m;
            while (r - l > 1) {
                int mid = (l + r) >> 1;
                if (roots[mid]->sum(la, mid) < ka) {
                    l = mid;
                } else{
                    r = mid;
                }
            }
            ans1.push_back(r);
            p = r;
        }
    }
}


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int num_test = 0;
    while(true + true){
        num_test++;
        if(num_test % 2 == 0){
            cout << num_test << endl;
        }
        srand(rand());
        n = rand() % 8 + 1;
        m = rand() % 8 + 1;
        for(int i = 0; i < n; ++i){
            input.push_back((rand() % n) + 1);
        }
        q = rand() % 4 + 1;
        for(int i = 0; i < q; ++i){
            int a = rand() % m + 1;
            int b = rand() % m + 1;
            taskss.push_back({a, b});
        }
        /*cout << n << " " << m << endl;
        for(auto x : input){
            cout << x << " ";
        }
        cout << endl << q << endl;
        for(auto x : taskss){
            cout << x.first << " " << x.second << endl;
        }*/
        solve();
        solve1();
        if(ans.size() != ans1.size()){
            cout << n << " " << m << endl;
            for(auto x : input){
                cout << x << " ";
            }
            cout << endl << q << endl;
            for(auto x : taskss){
                cout << x.first << " " << x.second << endl;
            }
            cout << "MY\n";
            for(auto x : ans){
                cout << x << " ";
            }
            cout << "\nGOOD\n";
            for(auto x : ans1){
                cout << x << " ";
            }
            cout << endl;
            return 0;
        }
        else{
            bool cmp = true;
            for(int i = 0; i < ans.size(); ++i){
                if(ans[i] != ans1[i]){
                    cmp = false;
                }
            }
            if(!cmp){
                cout << n << " " << m << endl;
                for(auto x : input){
                    cout << x << " ";
                }
                cout << endl << q << endl;
                for(auto x : taskss){
                    cout << x.first << " " << x.second << endl;
                }
                cout << "MY\n";
                for(auto x : ans){
                    cout << x << " ";
                }
                cout << "\nGOOD\n";
                for(auto x : ans1){
                    cout << x << " ";
                }
                cout << endl;
                return 0;
            }
        }
        ans.clear();
        ans1.clear();
        input.clear();
        taskss.clear();
    }
    return 0;
}
