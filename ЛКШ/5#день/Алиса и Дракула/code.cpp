#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

void solve(long long A, long long B) {
    long long ans = 0;
    if (B < 90) {
        for (; B > 0; --B) {
            ans = max(A / gcd(A, B) * B, ans);
        }
    } else {
        for (;; --B) {
            long long res = (gcd(A, B));
            ans = max(A / res * B, ans);
            if (res == 1) {
                break;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        long long A, B;
        cin >> A >> B;
        solve(A, B);
    }
    return 0;
}
