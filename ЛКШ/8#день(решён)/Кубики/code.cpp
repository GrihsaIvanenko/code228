#include <bits/stdc++.h>

using namespace std;

vector<int> z_function(vector<int> &v1) {
    int n = v1.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (v1[i + z[i]] == v1[z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r + 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    //z[0] = n;
    return z;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i){
        cin >> v[i];
    }
    for (int i = 0; i < n; ++i){
        v.push_back(v[n - i - 1]);
    }
    vector<int> res = z_function(v);
    set<int> ans;
    for (int i = n; i < n * 2; ++i){
       if (res[i] + i == n * 2 && res[i] % 2 == 0){
            ans.insert(n - res[i] / 2);
        }
    }
    ans.insert(n);
    for (auto x : ans){
        cout << x << " ";
    }
    return;
}

int main(){
    solve();
    return 0;
}
