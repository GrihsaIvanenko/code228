#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

const long long p = 29, mod = 1e9 + 7;

long long pw[MAXN + 1];

struct hasher{
    int lb, rb, mid;
    long long up_hash = 0, down_hash = 0;
    hasher *l = nullptr, *r = nullptr;
    hasher(int lb_, int rb_){
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        if (rb - lb != 1){
            l = new hasher(lb, mid);
            r = new hasher(mid, rb);
        }
    }
    void update(){
        if (rb - lb == 1){
            return;
        }
        up_hash = (l->up_hash + r->up_hash * pw[rb - mid]) % mod;
        down_hash = (l->down_hash * pw[mid - lb] + r->down_hash) % mod;
    }
    void upd(int pos, int del){
        if (rb - lb == 1){
            up_hash = down_hash = del;
            return;
        }
        if (pos < mid){
            l->upd(pos, del);
        }
        else{
            r->upd(pos, del);
        }
        update();
    }
    bool palindrom(int le, int re){
        return up(le, re) == down(le, re);
    }
    long long up(int le, int re){
        if (le >= rb || re <= lb){
            return 0;
        }
        if (le <= lb && rb <= re){
            return (up_hash * pw[lb - le]) % mod;
        }
        return (l->up(le, re) + r->up(le, re)) % mod;
    }
    long long down(int le, int re){
        if (le >= rb || re <= lb){
            return 0;
        }
        if (le <= lb && rb <= re){
            return (down_hash * pw[re - rb]) % mod;
        }
        return (l->down(le, re) + r->down(le, re)) % mod;
    }
    void print(){
        cout << lb << " " << rb << ": " << up_hash << " " << down_hash << endl;
        if (l != nullptr){
            l->print();
            r->print();
        }
    }
};

void solve(){
    pw[0] = 1;
    for (int i = 1; i <= MAXN; ++i){
        pw[i] = (pw[i - 1] * p) % mod;
    }
    string s;
    cin >> s;
    hasher *hashe = new hasher(0, MAXN);
    for (int i = 0; i < s.size(); ++i){
        hashe->upd(i, s[i] - 'a' + 1);
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        string t;
        cin >> t;
        if (t == "palindrome?"){
            int a, b;
            cin >> a >> b;
            --a;
            if (hashe->palindrom(a, b)){
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            int a;
            char b;
            cin >> a >> b;
            --a;
            hashe->upd(a, b - 'a' + 1);
        }
    }
}

int main(){
    solve();
    return 0;
}
