#include <bits/stdc++.h>

using namespace std;

const long long MOD = 998244353;

long long pow(long long x, long long pw) {
    if (pw == 0)
        return 1;
    if (pw % 2)
        return (x * pow(x, pw - 1)) % MOD;
    return pow((x * x) % MOD, pw / 2);
}

long long obr(long long x) {
    return pow(x, MOD - 2);
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    long long last = 0;
    for (int i = 0; i < n; ++i)
        last = ((((last + 1ll) * 100ll) % MOD) * obr(v[i])) % MOD;
    cout << last << '\n';
}
