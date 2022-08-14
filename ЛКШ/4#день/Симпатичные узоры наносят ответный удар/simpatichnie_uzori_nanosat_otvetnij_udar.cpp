#include <bits/stdc++.h>

using namespace std;

bool good(int aa, int bb, int m){
    for(int i = 0; i < m - 1; ++i){
        bool a = aa & (1 << i),
        b = aa & (1 << (i + 1)),
        c = bb & (1 << i),
        d = bb & (1 << (i + 1));
        if(a && b && c && d){
            return false;
        }
        if(!(a || b || c || d)){
            return false;
        }
    }
    return true;
}

bool is_null(string s){
    for(int i = 0; i < s.size() - 1; ++i){
        if(s[i] != '0'){
            return false;
        }
    }
    return s[s.size() - 1] == '1';
}

bool chet(string s){
    return !((s[s.size() - 1] - '0') % 2);
}

void inc(string &s){
    int i = s.size() - 1;
    while(s[i] == '0'){
        --i;
    }
    s[i]--;
    for(int j = i + 1; j < s.size(); ++j){
        s[j] = '9';
    }
}

void div_2(string &s){
    int ten = 0, will_ten = 0;
    for(int i = 0; i < s.size(); ++i){
        will_ten = (s[i] - '0') % 2;
        s[i] = (s[i] - '0' + ten * 10) / 2 + '0';
        ten = will_ten;
    }
}

int m, p;

string n;

vector<vector<int>> pw(vector<vector<int>> a, vector<vector<int>> b){
    int n = a.size();
    vector<vector<int>> res(n, vector<int>(n));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= p;
            }
        }
    }
    return res;
}

vector<vector<int>> pow(vector<vector<int>> v, string p){
    if(is_null(p)){
        return v;
    }
    if(chet(p)){
        div_2(p);
        return pow(pw(v, v), p);
    }
    inc(p);
    div_2(p);
    return pw(pow(pw(v, v), p), v);
}

void solve(){
    cin >> n >> m >> p;
    vector<vector<int>> v((1 << m), vector<int> (1 << m));
    for(int i = 0; i < (1 << m); ++i){
        for(int j = 0; j < (1 << m); ++j){
            if(good(i, j, m)){
                v[i][j] = 1;
            }
        }
    }
    inc(n);
    v = pow(v, n);
    int ans = 0;
    for(int i = 0; i < v.size(); ++i){
        for(int j = 0; j < v.size(); ++j){
            ans += v[i][j];
            ans %= p;
        }
    }
    cout << ans;
}

int main(){
    solve();
    return 0;
}
