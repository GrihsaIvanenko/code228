#include <bits/stdc++.h>

using namespace std;

long long f(long long add, long long c) {
    long long ans = 1;
    for (long long i = 1; i <= c; ++i)
        ans *= (add + i);
    for (long long i = 2; i <= c; ++i)
        ans /= i;
    return ans;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    long long n;
    cin >> n;
    long long len = 41, add = 9;
    while (len >= 0) {
        while (f(len, add) <= n) {
            n -= f(len, add);
            --add;
        }
        if (add != 9)
            cout << 9 - add;
        --len;
    }
    cout << '\n';
    return 0;
}
