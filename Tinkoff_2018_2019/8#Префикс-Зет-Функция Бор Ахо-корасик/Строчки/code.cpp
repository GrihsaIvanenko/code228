#include <bits/stdc++.h>

using namespace std;

vector<int> p_f(string s){
    int n = s.size();
    vector<int> p(n);
    for(int i = 1; i < n; ++i){
        int cur = p[i - 1];
        while(s[cur] != s[i] && cur > 0){
            cur = p[cur - 1];
        }
        if(s[i] == s[cur]){
            p[i] = cur + 1;
        }
    }
    return p;
}

int main(){
    string s, b;
    cin >> s >> b;
    if(s.size() != b.size()){
        cout << -1 << endl;
        return 0;
    }
    if(s == b){
        cout << 0 << endl;
        return 0;
    }
    vector<int> v = p_f(b + s + s);
    for(int i = b.size() + 2 * s.size() - 1; i > b.size() * 2 - 1; --i){
        if(v[i] % b.size() == 0 && v[i] != 0){
            int lox = s.size();
            cout << lox * 3 - i - 1 << endl;
            return 0;
        }
    //cout << i << " " << v[i] << endl;
    }
    cout << -1 << endl;
    return 0;
}
