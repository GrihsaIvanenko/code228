#include <bits/stdc++.h>

using namespace std;

struct segtree {
    int lb, rb, mean = 0, kolvo = 0;
    segtree *l = 0, *r = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    pair<int, int> ask(int pos){
        //cout << pos << " " << lb << " kkk " << rb << endl;
        if(rb <= pos){
            return {mean, kolvo};
        }
       // cout << pos << " " << lb << " kkk " << rb << endl;
        int t = (lb + rb) / 2;
        if(t >= pos){
            return l -> ask(pos);
        }
       // cout << pos << " " << lb << " kkk " << rb << endl;
        pair<int,int> p = l -> ask(pos), p1 = r ->ask(pos);
        if(p.first == p1.first){
            return {p.first, (p.second + p1.second) % 1000000007};
        }
        if(p.first > p1.first){
            return p;
        }
        return p1;
    }
    void build(int pos, int len, int kolvo1){
        if(lb + 1 == rb){
            if(mean == len + 1){
                kolvo += kolvo1;
                kolvo %= 1000000007;
            }
            else if(mean < len + 1){
                 mean = len + 1;
                kolvo = kolvo1;
            }
            return;
        }
        int t = (lb + rb) / 2;
        if(pos < t){
            l -> build(pos, len, kolvo1);
        }
        else{
            r -> build(pos, len, kolvo1);
        }
        if(l -> mean == r -> mean){
            kolvo = (l -> kolvo + r -> kolvo) % 1000000007;
            mean = l -> mean;
        }
        else if(l -> mean > r -> mean){
            kolvo = l -> kolvo;
            mean = l -> mean;
        }
        else{
            kolvo = r ->kolvo;
            mean = r -> mean;
        }
    }
     void ccc(){
        cout << mean  << " " << kolvo<< " " << lb << " " << rb << endl;
        if(l){
            l->ccc();
        }
        if(r){
            r->ccc();
        }
    }
};
int f(int n){
    if(n == 1){
        return 1;
    }
    return f((n + 1) / 2) * 2;
}
int main(){
    fstream fin("input.txt"), fout("output.txt");
    int n, x;
    fin >> n;
    vector<int> v(n), v1(n);
    segtree kek(0, f(n + 1));
    map<int, int> mm;
    for(int i = 0; i < n; ++i){
        fin >> x;
        v1[i] = v[i] = x;
    }
    sort(v1.begin(), v1.end());
    for(int i = 0; i < n; ++i){
        mm[v1[i]] = i + 1;
    }
    kek.build(0, 0, 1);

    for(int i = 0; i < n; ++i){
        pair<int, int> p = kek.ask(mm[v[i] ]);
        kek.build(mm[v[i] ], p.first, p.second);
    }
    fout << kek.kolvo << endl;
}
