#include <bits/stdc++.h>

using namespace std;

const long long two = 2;

int main()
{
    int g;
    cin >> g;
    for(int h = 0; h < g; ++h){
        pair<long long, pair<long long, long long>> mas[6];
        int l = 0, r = 60;
        for(int i = 0; i < 6; ++i){
            int mid = (l + r) / 2;
            long long ask = 1;
            for(int j = 0; j < mid; ++j){
                ask *= two;
            }
            cout << "X " << ask << endl;
            long long a, b;
            cin >> a >> b;
            mas[i] = {mid, {a, b}};
            if(a == 0){
                r = mid;
            }
            else{
                l = mid;
            }
        }
        long long ans = 0;
        for(int i = 0; i < 6; ++i){
            if(mas[i].first == l){
                ans = mas[i].second.second;
            }
        }
        cout << "N " << ans << endl;
        string s;
        cin >> s;
        if(s == "Wrong"){
            return 0;
        }
    }
    return 0;
}

