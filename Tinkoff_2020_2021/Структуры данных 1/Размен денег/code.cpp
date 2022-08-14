#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 262144;

using ll = long long;

ll vals[MAXN];

vector<ll> otr[MAXN + MAXN], sums[MAXN + MAXN];

ll get_ls(int id, int who) {
    return sums[id][upper_bound(otr[id].begin(), otr[id].end(), who) - otr[id].begin()];
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> vals[i];
    for (int i = MAXN; i < (MAXN << 1); ++i) {
        otr[i].push_back(vals[i - MAXN]);
        sums[i].push_back(0);
        sums[i].push_back(vals[i - MAXN]);
    }
    for (int i = MAXN - 1; i > 0; --i) {
        merge(otr[i + i].begin(), otr[i + i].end(), otr[i + i + 1].begin(), otr[i + i + 1].end(), back_inserter(otr[i]));
        sums[i].resize(otr[i].size() + 1);
        for (size_t j = 0; j < otr[i].size(); ++j)
            sums[i][j + 1] = sums[i][j] + otr[i][j];
    }
    for (int q = 0; q < m; ++q) {
        int l, r;
        cin >> l >> r;
        --l;
        vector<int> inds;
        l += MAXN;
        r += MAXN;
        while (l < r) {
            if (l & 1) {
                inds.push_back(l);
                ++l;
            }
            if (r & 1) {
                --r;
                inds.push_back(r);
            }
            l >>= 1;
            r >>= 1;
        }
        ll ans = 1;
        while (true) {
            ll cur = 1;
            for (auto x : inds) {
                cur += get_ls(x, ans);
            }
            // assert(cur >= ans);
            if (cur <= ans) {
                cout << ans << '\n';
                break;
            } else {
                ans = cur;
            }
        }
    }
    return 0;
}
