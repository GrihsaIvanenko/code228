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
    string s;
    cin >> s;
    vector<int> v = p_f(s);
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    return 0;
}

