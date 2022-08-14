#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5;

signed main() {
    int n, k, m;
    cin >> n >> k >> m;
    if (n - k - k + 1 < 0) {
        cout << 0 << '\n';
        return 0;
    }
    vector<int> lp(MAXN + 1), simple;
    lp[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            simple.push_back(i);
        }
        for (int j = 0; j < simple.size() && simple[j] <= i && simple[j] * i <= MAXN; ++j)
            lp[i * simple[j]] = simple[j];
    }
    vector<int> cnt(MAXN + 1);
    for (int i = 2; i <= n - k + 1; ++i) {
        int ii = i;
        while (lp[ii] != 1) {
            ++cnt[lp[ii]];
            ii /= lp[ii];
        }
    }
    for (int i = 2; i <= k; ++i) {
        int ii = i;
        while (lp[ii] != 1) {
            --cnt[lp[ii]];
            ii /= lp[ii];
        }
    }
    for (int i = 2; i <= n - k - k + 1; ++i) {
        int ii = i;
        while (lp[ii] != 1) {
            --cnt[lp[ii]];
            ii /= lp[ii];
        }
    }
    int ans = 1;
    for (int i = 0; i <= n; ++i) {
        while (cnt[i] != 0) {
            ans = (ans * i) % m;
            --cnt[i];
        }
    }
    cout << ans << endl;
    return 0;
}
