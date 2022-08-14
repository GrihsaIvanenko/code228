#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> k(n);
    vector<vector<int>> v(n, vector<int>(n));
    for(int i = 0; i < n; ++i){
        int l;
        cin >> l;
        k[i] = {l, i};
    }
    for(int i = 0; i < n; ++i){
        sort(k.begin(), k.end());
        int l = k[0].first;
        int m = k[0].second;
        for(int j = 0; j < k.size() - 1; ++j){
            k[j] = k[j + 1];
        }
        k.resize(k.size() - 1);
        for(int j = 0; j < l; ++j){
            k[j].first--;
            v[m][k[j].second] = v[k[j].second][m] = 1;
        }
        for(int j = l; j < k.size(); ++j){
            //cout << "sss ";
            k[j].first -= 2;
            v[m][k[j].second] = 0;
            v[k[j].second][m] = 2;
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
