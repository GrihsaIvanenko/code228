#include <bits/stdc++.h>

using namespace std;

vector<int> suffix_array(string s){
    s.push_back(0);
    int n = s.size();
    vector<int> c(n), ans(n);
    map<int,vector<int>> mm;
    for(int i = 0;  i < n; ++i)
        mm[s[i]].push_back(i);
    int cnt = 0, cls = 0;
    for(auto x : mm){
        for(auto y : x.second)
            c[y] = cls, ans[cnt++] = y;
        ++cls;
    }
    for(int len = 1; cls < n; ++len){
        vector<vector<int>> sorter(cls);
        vector<int> n_cls(n);
        int d = (1<<len)>>1;
        int new_cls = cnt = 0;
        for(int i = 0; i < n; ++i){
            int k = (ans[i] - d + n) % n;
            sorter[c[k] ].push_back(k);
        }
        for(int i = 0; i < cls; ++i){
            for(int j = 0; j < sorter[i].size(); ++j){
                if(j == 0 || c[(sorter[i][j] + d) % n] != c[(sorter[i][j - 1] + d) % n])
                    ++new_cls;
                n_cls[sorter[i][j] ] = new_cls - 1;
                ans[cnt++] = sorter[i][j];
            }
        }
        c =  n_cls;
        cls = new_cls;
    }
    return vector<int>(ans.begin() + 1, ans.end());
}


int main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    string s;
    cin >> s;
    vector<int> ans = suffix_array(s);
    for(int i = 0;i < s.size(); ++i)
        cout << ans[i] + 1 << " ";
    cout << endl;
    return 0;
}
