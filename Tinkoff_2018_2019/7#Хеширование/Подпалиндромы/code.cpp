#include <bits/stdc++.h>

using namespace std;

vector<long long> hesh, r_hesh, p;

long long mod = 1000000013;

int n;

long long get_hesh (int l, int r) {
    return (hesh[r] - hesh[l] + mod) % mod * p[l] % mod;
}

long long get_r_hesh (int l, int r) {
    return (r_hesh[r] - r_hesh[l] + mod) % mod * p[n - r] % mod;
}

int main()
{
    string s;
    cin >> s;
    n = s.size();
    p.resize(n);
    hesh.resize(n + 1);
    r_hesh.resize(n + 1);
    p[0] = 1;
    for(int i = 1; i < n; ++i){
        p[i] = p[i - 1] * 27 % mod;
    }
    hesh[0] = 0;
    r_hesh[0] = 0;
    for(int i = 1; i <= n; ++i){
        int krak = s[i - 1] - 'a' + 1;
        r_hesh[i] = (r_hesh[i - 1] + krak * p[i - 1]) % mod;
        hesh[i] = (hesh[i - 1] + krak * p[n - i]) % mod;
    }
    long long answer = 0;
    for(int i = 0; i < n; ++i){
        long long l = 1;
        int r = min(i, n - i - 1) + 2;
        while(l + 1 < r){
            int mid = (l + r) / 2;
            if(get_hesh(i - mid + 1, i + 1) == get_r_hesh(i, i + mid)){
                l = mid;
            }
            else{
                r = mid;
            }
        }
        answer += l;
    }
    for(int i = 0; i < n - 1; ++i){
        if(s[i] != s[i + 1]){
            continue;
        }
        long long l = 1;
        int r = min(i, n - i - 2) + 2;
        while(l + 1 < r){
            int mid = (l + r) / 2;
            if(get_hesh(i - mid + 1, i + 1) == get_r_hesh(i + 1, i + mid + 1)){
                l = mid;
            }
            else{
                r = mid;
            }
        }
        answer += l;
    }
    cout << answer << endl;
    return 0;
}

