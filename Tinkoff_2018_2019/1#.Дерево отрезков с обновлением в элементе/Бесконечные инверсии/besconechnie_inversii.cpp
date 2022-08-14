#include <bits/stdc++.h>

using namespace std;

#define pb push_back

int to_pow_two(int x){
    if(x == 1)return 0;
    return to_pow_two((x + 1)>>1) + 1;
}

void solve(){
    int n;
    cin >> n;
    vector<pair<int,int>> tasks;
    vector<int> recompress;
    map<int,int> compress;
    for(int i = 0; i < n; ++i){
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        tasks.pb({a, b});
        recompress.pb(a);
        recompress.pb(b);
    }
    sort(recompress.begin(), recompress.end());
    recompress.resize(unique(recompress.begin(), recompress.end()) - recompress.begin());
    for(int i = 0; i < recompress.size(); ++i)
        compress[recompress[i] ] = i;
    for(int i = 0; i < n; ++i)
        swap(recompress[compress[tasks[i].first ] ], recompress[compress[tasks[i].second] ]);
    int sizer = to_pow_two(recompress.size());
    int deot[1<<(sizer + 1)];
    for(int i = 0; i < (1<<(sizer + 1)); ++i)
        deot[i] = 0;
    long long ans = 0;
    for(int i = 0; i < recompress.size(); ++i){
        int pos = compress[recompress[i] ] + (1<<sizer);
        for(int j = 0; j < sizer; ++j){
            if(pos % 2 == 0)
                ans += deot[pos + 1];
            deot[pos]++;
            pos = (pos>>1);
        }
    }
    //cout << ans << endl;
    vector<int> tmp(recompress.size());
    for(int i = 0; i < recompress.size(); ++i)
        tmp[i] = recompress[i];
    sort(recompress.begin(), recompress.end());
    /*for(int i = 0; i < recompress.size(); ++i)
        cout << tmp[i] << " ";
    cout << endl;
    for(int i = 0; i < recompress.size(); ++i)
        cout << recompress[i] << " ";
    cout << endl;*/
    for(int i = 0; i < tmp.size(); ++i){
        if(tmp[i] > recompress[i]){
            int l = i, r = tmp.size();
            while(r - l > 1){
                int mid = (l + r)>>1;
                if(tmp[i] >= recompress[mid])
                    l = mid;
                else
                    r = mid;
            }
            ans += tmp[i] - recompress[i] + i - l;
        }
        else{
            int l = -1, r = i;
            while(r - l > 1){
                int mid = (l + r + 1)>>1;
                if(tmp[i] <= recompress[mid])
                    r = mid;
                else
                    l = mid;
            }
            ans += recompress[i] - tmp[i] + r - i;
        }
    }
    cout << ans << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
