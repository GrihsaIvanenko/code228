#include <bits/stdc++.h>

using namespace std;

int main(){
    int lel = 1 + 1;
    freopen("battleship.in", "r", stdin);
   freopen("battleship.out", "w", stdout);
    vector<vector<int>> v(10, vector<int> (10));
    int x = 1;
    int xx  = 9, xy = 1;
    for(int i = 1; i < 101; ++i){
        cin >> x;
        if(x == 100){
            xx = i / 10; xy = i % 10;
        }
    }
   // xx++;
    xx++;
  //  cout << xx << " " << xy << endl;
  if(xy == 0){
        xy = 10;
        xx--;
    }
    vector<vector<int>> ans(12, vector<int>(12));
    for(int j = max(0,xx - 1); j < xx + 2; ++j){
        for(int i = 0; i < 12; ++i){
            ans[j][i] = 1;
        }
    }

   // /cout << "SSSSS";
    ans[xx][xy] = 2;
    vector<vector<int>> peta(3);
    peta[0] = {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0};
    peta[1] = {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0};
    peta[2] = {0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0};
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 10; ++j){
            peta[i][j]++;
          //  cout << peta[i][j];
        }
        //cout << endl;
    }
    for(int i = 1; i < 11; ++i){
        if(ans[i][1] == 0 && peta.size() > 0){
            ans[i] = peta[peta.size() - 1];
           // cout << "HAPPY" << endl;
            peta.pop_back();
            for(int h = 1; h < 11; ++h){
                ans[i + 1][h] = 1;
            }
        }
    }
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            if(ans[i + 1][j + 1] == 2){
                cout << '#';
            }
            else{
                cout << '.';
            }
        }
        cout << endl;
    }
}
