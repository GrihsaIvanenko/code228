#include <bits/stdc++.h>

using namespace std;

#define int long long

pair<int,bool> verdict(int a, int b, int c){
    //cout << a << " " << b << " my " << c << endl;
    if(c < ((a - b)>>1)) {
           // cout << 0 << "my\n";
        return {0, 0};
    }
    if(c < ((a - b + 1)>>1) ){
        //cout << 1 << "my\n";
        return {1, 1};
    }
    //cout << 2 << "my\n";
    return {1, 0};
}

//vector<int> l_dp, r_dp, v;

pair<int, bool> f(vector<int> &l_dp, vector<int> &r_dp, int power, vector<int> &v){
    int ll = 0, rl = v.size(), lr = -1, rr = v.size() - 1;
    while(rl - ll > 1){
        int midl = (rl + ll)>>1;
        if(l_dp[midl] + 1 > power)
            rl = midl;
        else
            ll = midl;
    }
    while(rr - lr > 1){
        int midr = (lr + rr)>>1;
        if(r_dp[midr] + 1 > power)
            lr = midr;
        else
            rr = midr;
    }
    if(((v[rr] - v[ll])>>1) > power) {
        return {0, 0};
    }
    if(((v[rr] + 1 - v[ll])>>1) > power) {
        return {1, 1};
    }
    return {1, 0};
}


signed main(){
    int n;
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    vector<int> l_dp(n), r_dp(n);
    l_dp[0] = r_dp[n - 1] = 0;
    int r_now = 0, last_it = 0;
    for(int i = 1; i < n; ++i){
       int l = 0, r = i;
       while(r - l > 2){
            int midl = (l + l + r) / 3,
            midr = (l + r + r) / 3;
            if(max(v[i] - v[midl], l_dp[midl] + 1) > max(v[i] - v[midr], l_dp[midr] + 1)){
                l_dp[i] = max(v[i] - v[midr], l_dp[midr] + 1);
                l = midl;
            }
            else{
                l_dp[i] = max(v[i] - v[midl], l_dp[midl] + 1);
                r = midr;
            }
       }
       if(max(v[i] - v[l], l_dp[l] + 1) > max(v[i] - v[r - 1], l_dp[r - 1] + 1)){
            l_dp[i] = max(v[i] - v[r - 1], l_dp[r - 1] + 1);
        }
        else{
            l_dp[i] = max(v[i] - v[l], l_dp[l] + 1);
        }
    }
    for(int i = n - 2; i > -1; --i){
        int l = i + 1, r = n;
       while(r - l > 2){
            int midl = (l + l + r) / 3,
            midr = (l + r + r) / 3;
            if(max(v[midl] - v[i], r_dp[midl] + 1) > max(v[midr] - v[i], r_dp[midr] + 1)){
                r_dp[i] = max(v[midr] - v[i], r_dp[midr] + 1);
                l = midl;
            }
            else{
                r_dp[i] = max(v[midl] - v[i], l_dp[midl] + 1);
                r = midr;
            }
       }
        --r;
       // cout << l << " " << r << " " << v[l] << " " << v[r] << " " << v[i] << " " << r_dp[l] << " " << r_dp[r] << endl;
       if(max(v[l] - v[i], r_dp[l] + 1) > max(v[r] - v[i], r_dp[r] + 1)){
            //cout << v[r] - v[i] << " " << r_dp[r] + 1 << endl;
            r_dp[i] = max(v[r] - v[i], r_dp[r] + 1);
        }
        else{
            //cout << v[l] - v[i] << " " << r_dp[l] + 1 << endl;
            r_dp[i] = max(v[l] - v[i], r_dp[l] + 1);
        }
       // cout << i << " dp " << r_dp[i] << endl;
    }
    /*for(auto x : l_dp)
        cout << x << " ";
    cout << endl;
    for(auto x : r_dp)
        cout << x << " ";
    cout << endl;*/
    int l_ans = 0, r_ans = v[n - 1] + 1;
    bool imba = false;
    while(r_ans - l_ans > 1){
        int mid_ans = (l_ans + r_ans)>>1;
        pair<int, bool> get = f(l_dp, r_dp, mid_ans, v);
        //cout << mid_ans << " " << get.first << " " << get.second << endl;
        imba = get.second;
        if(get.first == 0)
            l_ans = mid_ans;
        else
            r_ans = mid_ans;
    }
    pair<int, bool> get = f(l_dp, r_dp, l_ans, v);
    if(get.first == 1){
        cout << l_ans << ".";
        if(get.second)cout << "5";
        else cout << "0";
        cout << '\n';
        return 0;
    }
    get = f(l_dp, r_dp, r_ans, v);
    //cout << get.first << " " << get.second << endl;
    //cout << r_ans << " " << get.first << " " << get.second << endl;
    if(get.second)cout << r_ans << ".5\n";
    else cout << r_ans << ".0\n";
    return 0;
}
