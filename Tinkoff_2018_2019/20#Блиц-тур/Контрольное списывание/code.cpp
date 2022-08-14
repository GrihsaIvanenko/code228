#include <bits/stdc++.h>

using namespace std;

vector<int> c[18];

int maxl = 0;

vector<int> suff_mass(string s){
    s.push_back(0);
    int n = s.size();
    vector<int> ans(n);
    for(int i = 0; i < 18; ++i)c[i].resize(n);
    map<int, vector<int>> mm;
    for(int i = 0; i < n; ++i)mm[s[i]].push_back(i);
    int cnt = 0, cls = 0;
    for(auto x : mm){
        for(auto y : x.second){
            c[0][y] = cls, ans[cnt++] = y;
        }
        ++cls;
    }
    for(int len = 1; cls < n; ++len){
        vector<vector<int>> to_sort(cls);
        int d = (1<<len)>>1;
        int new_cls = cnt = 0;
        for(int i = 0; i < n; ++i){
            int k = (ans[i] - d + n) % n;
            to_sort[c[len - 1][k]].push_back(k);
        }
        for(int i = 0; i < cls; ++i){
            for(int j = 0; j < to_sort[i].size(); ++j){
                if(j == 0 || c[len - 1][(to_sort[i][j]+ d) % n] != c[len - 1][(to_sort[i][j - 1] + d) % n])
                    ++new_cls;
                c[len][to_sort[i][j]] = new_cls - 1;
                ans[cnt++] = to_sort[i][j];
            }
        }
        cls = new_cls;
        maxl = len;
    }
    return vector<int> (ans.begin() + 1, ans.end());
}

int main(){
    string str// = "abacaba";for(int i = 0; i < str.size(); ++i)cout << str[i] << " ";cout << endl;
    ;
    freopen("kthsubstr.in", "r", stdin);
   freopen("kthsubstr.out", "w", stdout);
    cin >> str;
    vector<int> sf = suff_mass(str);
    //for(auto x : sf)cout << x << " ";cout << "sf\n";
    vector<int> lcp(sf.size());
    int n = str.size();
    for(int i = 1; i < n; ++i){
        int a = sf[i - 1], b = sf[i], start = maxl, ans = 0;
        for(int ij = maxl; ij > -1; --ij){
            if(c[ij][a] == c[ij][b]){
                ans += 1<<ij;
                a += 1<<ij;
                b += 1<<ij;
            }
        }
        lcp[i] = ans;
    }
   /* for(int i = 0; i <= maxl; ++i){
        for(int j = 0; j < n; ++j){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }*/
    /*for(int i = 0; i < n; ++i){
        cout << i << " " << sf[i] << " " << lcp[i] << " " << str.substr(sf[i], str.size() - sf[i]) << endl;
    }*/
   long long k;
   cin >> k;
   for(int i = 0; i < n; ++i){
    if(k > n - sf[i] - lcp[i])k -= (n - sf[i] - lcp[i]);
    else{
        cout << str.substr(sf[i], k + lcp[i]);
        return 0;
    }
   }
   cout << str.substr(sf[n - 1], n - sf[n - 1]);
   return 0;
}
