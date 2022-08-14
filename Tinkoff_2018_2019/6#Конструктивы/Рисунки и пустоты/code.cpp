#include <bits/stdc++.h>

using namespace std;

int main() {
    int kek;
    cin >> kek; for(int heh = 0; heh < kek; ++heh){
    int n, w, h;
    cin >> h >> w >> n;
    vector<vector<int>> v(h, vector<int>(w));
    for(int i = 1; i < h - 1; ++i){
        for(int j = 1; j < w - 1; ++j){
            v[i][0] = v[i][w - 1] = 0;
            if((i + j) % 2){
                 v[i][j] = 0;
            }
            else{
                if(n > 0){
                    v[i][j] = 1;
                    n--;
                }
                else{
                    v[i][j] = 0;
                }
            }
        }
    }
    if(n > 0){
        cout << "Impossible" << endl;
    }
    else{
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                if(v[i][j] == 0){
                    cout << '.';
                }
                else{
                    cout << '#';
                }
            }
            cout << endl;
        }
   }
    cout << endl;
    }
    return 0;
}

