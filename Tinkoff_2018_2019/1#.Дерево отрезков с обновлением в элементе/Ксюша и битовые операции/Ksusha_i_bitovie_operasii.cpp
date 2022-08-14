#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k, a, b;
    cin >> n >> m;
    k = 1<<n;
    vector<int> v[n + 1];
    int size = 1;
    for(int i = n; i > -1; --i){
        v[i].resize(size);
        size *= 2;
    }
    for(int i = 0; i < k; ++i){
        cin >> v[0][i];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < v[i].size(); ++j){
            if(i % 2){
                v[i][j] = v[i - 1][j * 2] | v[i - 1][j * 2 + 1];
            }
            else{
                v[i][j] = v[i - 1][j * 2] ^ v[i - 1][j * 2 + 1];
            }
        }
    }
    for(int i = 0; i < m; ++i){
        cin >> a >> b;
        --a;
        v[0][a] = b;
        a = a>>1;
        for(int j = 1; j <= n; ++j){
            if(j % 2){
                v[j][a] = v[j - 1][a * 2] | v[j - 1][a * 2 + 1];
            }
            else{
                v[j][a] = v[j - 1][a * 2] ^ v[j - 1][a * 2 + 1];
            }
            a = a>>1;
        }
        cout << v[n][0] << endl;
    }
    return 0;
}
