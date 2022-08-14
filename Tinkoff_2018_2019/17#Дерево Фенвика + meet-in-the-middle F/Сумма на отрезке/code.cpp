#include <bits/stdc++.h>

using namespace std;

int main(){
    long long n, k;
    cin >> n >> k;
    long long fenvic[n + 1];
    long long adecvat[n + 1];
    for(long long i = 0; i <= n; ++i)fenvic[i] = adecvat[i] = 0;
    for(long long i = 0; i < k; ++i){
        char it;
        long long l, r;
        cin >> it >> l >> r;
        if(it == 'A'){
                swap(r, adecvat[l]);
                r = adecvat[l] - r;
                for(long long I = l; I <= n; I += (I & -I))fenvic[I] += r;
        }
        else{
            long long ans = 0;
            for(long long I = r; I > 0; I -= (I & -I))ans += fenvic[I];
            for(long long I = l - 1; I > 0; I -= (I & -I))ans -= fenvic[I];
            cout << ans << endl;
        }
    }
    return 0;
}
