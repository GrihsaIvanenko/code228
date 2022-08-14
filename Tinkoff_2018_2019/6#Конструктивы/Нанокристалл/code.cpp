#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    if(n == 2 || n == 5){
        cout << "0 0";
        return 0;
    }
    if(n == 1){
        cout << "2 1" << endl << "1 2";
        return 0;
    }
    int res;
    for(int i = 1; i * (i - 1) / 2 <= n; ++i){
        res = i;
    }
    if(n + 1== (res)*(res + 1) / 2){
        cout << res << " " << (res - 2) * (res - 1) / 2 << endl;
        for(int i = 0; i < res - 1; ++i){
            for(int j = i + 1; j < res - 1; ++j){
                if(j != 1){
                    cout << i + 1 << " " << j + 1 << endl;
                }
            }
        }
        cout << res - 1 << " " << res << endl;
        return 0;
    }
    //cout << 2 * (res - 1) - (n - ((res - 1) * (res - 2) / 2)) << endl;
    //return 0;
    cout << res << " " << (res - 2) * (res - 1) / 2 + 2 * (res - 1) - (n - ((res - 1) * (res - 2) / 2))<< endl;
    for(int i = 0; i < res - 1; ++i){
        for(int j = i + 1; j < res - 1; ++j){
                cout << i + 1 << " " << j + 1 << endl;
        }
    }
    for(int i = 0; i <  2 * (res - 1) - (n - ((res - 1) * (res - 2) / 2)); ++i){
        cout << i + 1 << " " << res << endl;
    }
    return 0;
}

