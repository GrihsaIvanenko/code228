#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, now = 1, ch = 1;
    cin >> n;
    while(n * 2 >= (now + 2) * (now + 1))now++;
    cout << now << endl;
    vector<vector<int>> v(now);
    for(int i = 0; i < n; ++i){
        if(now != 0){
            v[ch - 1].push_back(i + 1);
            if(ch == now){
                ch = 0;
                now--;
            }
            ch++;
        }
        else{
            v[0].push_back(i + 1);
        }
    }
    for(int i = 0; i < v.size(); ++i){
        cout << v[i].size() << " ";
        for(int j = 0; j < v[i].size(); ++j){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

