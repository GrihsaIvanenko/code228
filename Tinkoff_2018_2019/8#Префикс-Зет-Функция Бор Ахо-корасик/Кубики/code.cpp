#include <bits/stdc++.h>

using namespace std;

vector<long long> hesh, r_hesh, p;

long long mod = 1000000013, n, pe, krak;

long long get_hesh (int l, int r) {
    return (hesh[r] - hesh[l] + mod) % mod * p[l] % mod;
}

long long get_r_hesh (int l, int r) {
    return (r_hesh[r] - r_hesh[l] + mod) % mod * p[n - r] % mod;
}

int main()
{
    cin >> n >> pe;
    pe++;
    p.resize(n);
    hesh.resize(n + 1);
    r_hesh.resize(n + 1);
    p[0] = 1;
    for(int i = 1; i < n; ++i){
        p[i] = p[i - 1] * pe % mod;
    }
    hesh[0] = 0;
    r_hesh[0] = 0;
    for(int i = 1; i <= n; ++i){
        cin >> krak;
        r_hesh[i] = (r_hesh[i - 1] + krak * p[i - 1]) % mod;
        hesh[i] = (hesh[i - 1] + krak * p[n - i]) % mod;
    }
    for(int i = 1; i <= n / 2; ++i){
        if(get_hesh(0, i) == get_r_hesh(i, 2 * i)){
            cout << n - i << " ";
        }
       // cout << get_hesh(0, i) << " " << get_r_hesh(i, 2 * i) << endl;
    }
    cout << n << endl;
    return 0;
}

