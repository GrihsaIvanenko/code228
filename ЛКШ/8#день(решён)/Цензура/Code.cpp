#include <bits/stdc++.h>

using namespace std;

const int MAXL = 500;

int n;

void sum(vector<int> & res, vector<int> &a, vector<int> &b){
    int tmp = 0;
    for (int i = MAXL - 1; i >= 0; --i){
        int aa = a[i], bb = b[i];
        res[i] = (aa + bb + tmp) % 10;
        tmp = (aa + bb + tmp) / 10;
    }
}

void null(vector<int> &res){
    for (int i = 0; i < MAXL; ++i){
        res[i] = 0;
    }
}

void print(vector<int> &v){
    int it = 0;
    while (it < v.size() && v[it] == 0){
        ++it;
    }
    if (it == v.size()){
        cout << 0 << endl;
        return;
    }
    for (int i = it; i < v.size(); ++i){
        cout << v[i];
    }
    cout << endl;
}

struct segment{
    segment() {
        go.assign(n, -1);
        dp.resize(MAXL);
        res_dp.resize(MAXL);
    }
    vector<int> go;
    vector<int> terminal;
    int suff = -1, long_suff = -1;
    bool used = false;
    vector<int> dp, res_dp;
};

struct coras{
    vector<segment> trie;
    coras() {
        trie.resize(1);
    }
    void eat(string s, int pos, int id = 0) {
        if (s.size() == 0) {
            trie[id].terminal.push_back(pos);
            return;
        }
        if (trie[id].go[(int(s[0]) - 33)] == -1) {
            segment t;
            trie[id].go[int(s[0])- 33] = trie.size();
            trie.push_back(t);
        }
        eat(s.substr(1), pos, trie[id].go[int(s[0])- 33]);
    }
    void build() {
        trie[0].suff = trie[0].long_suff = 0;
        deque<int> q;
        for (int i = 0; i < n; ++i) {
            if (trie[0].go[i] == -1) {
                trie[0].go[i] = 0;
            }
            else{
                q.push_back(trie[0].go[i]);
                trie[trie[0].go[i]].suff = 0;
                trie[trie[0].go[i]].long_suff = 0;
            }
        }
        while (!q.empty()) {
            int id = q.front();
            q.pop_front();
            for (int i = 0; i < n; ++i) {
                if (trie[id].go[i] == -1) {
                    trie[id].go[i] = trie[trie[id].suff].go[i];
                } else {
                    q.push_back(trie[id].go[i]);
                    trie[trie[id].go[i]].suff = trie[trie[id].suff].go[i];
                    if (trie[trie[trie[id].go[i]].suff].terminal.size() != 0) {
                        trie[trie[id].go[i]].long_suff = trie[trie[id].go[i]].suff;
                    }
                    else{
                        trie[trie[id].go[i]].long_suff = trie[trie[trie[id].go[i]].suff].long_suff;
                    }
                }
            }
        }
    }
    void debug() {
        int id = 0;
        while (true + true) {
            cout << "id: " << id << endl;
            cout << "print: 0-exit; 1-go(input); 2-go; 3-suff, l_suff, terminal\n";
            int tmp;
            cin >> tmp;
            if (tmp == 0) {
                return;
            } else if (tmp == 1) {
                cin >> id;
            } else if (tmp == 2) {
                for (int i = 0; i < n; ++i) {
                    cout << i << "->" << trie[id].go[i] << "  ";
                }
                cout << endl;
            } else{
                cout << trie[id].suff << "-suff " << trie[id].long_suff << "-long_suff ";
                for (auto x : trie[id].terminal) {
                    cout << x << " ";
                }
                cout << "is terminal\n";
            }
        }
    }
    void make_dp(int m){
        vector<int> one(MAXL), res(MAXL);
        one[MAXL - 1] = 1;
        trie[0].dp = one;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < trie.size(); ++j){
                for (int k = 0; k < n; ++k){
                    sum(trie[trie[j].go[k]].res_dp, trie[trie[j].go[k]].res_dp, trie[j].dp);
                }
            }
            for (int j = 0; j < trie.size(); ++j){
                if (trie[j].terminal.size() == 0 && trie[j].long_suff == 0){
                    for (int k = 0; k < MAXL; ++k){
                        trie[j].dp[k] = trie[j].res_dp[k];
                    }
                }
                null(trie[j].res_dp);
                //print(trie[j].dp);
            }
        }
        one[MAXL - 1] = 0;
        for (int i = 0; i < trie.size(); ++i){
            sum(res, one, trie[i].dp);
            for (int j = 0; j < MAXL; ++j){
                one[j] = res[j];
            }
        }
        print(one);
    }
};

void solve(){
    int m, p;
    cin >> n >> m >> p;
    map<char, int> mm;
    for (int i = 0; i < n; ++i){
        char t;
        cin >> t;
        mm[t] = 33 + i;
    }
    n = mm.size();
    coras corasic;
    for (int i = 0; i < p; ++i){
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); ++j){
            s[j] = char(mm[s[j]]);
        }
        corasic.eat(s, i);
    }
    corasic.build();
    corasic.make_dp(m);
}

int main(){
    solve();
    return 0;
}

// 20 3 10 abcdefghijklmnopqrst a b c ab bc ca ed hh s j
