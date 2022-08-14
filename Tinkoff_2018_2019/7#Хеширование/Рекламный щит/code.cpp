#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k, n, m;
    cin >> k >> n >> m;
    vector<vector<vector<int>>> v(k, vector<vector<int>>(n, vector<int>(m)));
    for(int i = 0; i < k; ++i){
        for(int j = 0; j < n; ++j){
            for(int ka = 0; ka < m; ++ka){
                char lox;
                cin >> lox;
                if(lox == '*'){
                    v[i][j][ka] = 2;
                }
                else{
                    v[i][j][ka] = 1;
                }
            }
        }
    }
    set<long long> hashs;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            long long hash = 0;
            for(int ka = 0; ka < k; ++ka){
                hash = (hash * 3 + v[ka][i][j]) % 1000000013;
            }
            hashs.insert(hash);
        }
    }
    cout << hashs.size();
    return 0;
}

