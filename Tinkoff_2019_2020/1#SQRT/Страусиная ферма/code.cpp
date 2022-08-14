#include <bits/stdc++.h>

using namespace std;

bool bad(long long a, long long b, long long c) {
    if (b <= a) {
        return b + b - 1 != c;
    }
    return a + a != c;
}

int main() {
    long long x;
    cin >> x;
    vector<pair<long long, long long>> ans;
    for (long long i = 1; i < 100000; ++i) {
        int n, m;
        if (i % 2) {
            m = (i + 1ll) / 2ll;
            n = (x + i - m) / (m + m + 1ll);
            if (bad(n, m, i)) continue;
        } else {
            n = i / 2ll;
            m = (x + i - n) / (n + n + 1ll);
            if (bad(n, m, i)) continue;
        }
        if (2ll * n * m + n + m == x + i) {
            ans.push_back({n, m});
        }
    }
    cout << ans.size() << endl;
    for (auto x : ans)
        cout << x.first << " " << x.second << endl;
    return 0;
}
