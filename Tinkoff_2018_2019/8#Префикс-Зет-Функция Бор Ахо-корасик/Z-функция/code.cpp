#include <bits/stdc++.h>

using namespace std;

vector<int> z_f(string s){
    vector<int> p(s.size());
    int l = 0, r = 0;
    for(int i = 1; i < s.size(); ++i){
        if(i > r){
            l = i;
            int lol = 0;
            while(lol + i < s.size() && s[lol] == s[lol + i]){
                lol++;

            }
            r = lol + i - 1;
            p[i] = lol;
        }
        else{
            if(i + p[i - l] < r){
                p[i] = p[i - l];
            }
            else{
                l = i;
                while(r < s.size() && s[r] == s[r - i]){
                    r++;
                }
                p[i] = r - i;
            }
        }
    }
    return p;
}

int main(){
    string s;
    cin >> s;
    vector<int> v = z_f(s);
    cout << s.size() << " ";
    for(int i = 1; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    return 0;
}


