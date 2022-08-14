#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1e9 + 7;

int gt(int x) {
    if (x == 4)
        return 0;
    if (x == 5)
        return 1;
    if (x == 7)
        return 2;
    if (x == 8)
        return 3;
    assert(false);
    return -1;
}

void solve() {
    int n, l;
    cin >> n >> l;
    vector<pair<int, pair<int, int>>> v(n);
    for (int i = 0; i < n; ++i) {
        int t = 0, len;
        string a, b;
        cin >> len >> a >> b;
        int aa = 0, bb = 0;
        if (a == "in")
            aa = -1;
        if (a == "out")
            aa = 1;
        t *= 3;
        if (b == "in")
            bb = -1;
        if (b == "out")
            bb = 1;
        v[i] = {len, {aa, bb}};
    }
    int ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int tmp = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                tmp += v[i].first;
        if (tmp != l)
            continue;
        int kolvo_op = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                if (v[i].second.first == 0)
                    ++kolvo_op;
        if (kolvo_op != 1)
            continue;
        int kolvo_cl = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                if (v[i].second.second == 0)
                    ++kolvo_cl;
        if (kolvo_cl != 1)
            continue;
        int O = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                if (v[i].second.first == 0)
                    O = v[i].second.second;
        vector<int> able(n);
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                if (v[i].second.first != 0 && v[i].second.second != 0) {
                    able[i] = 1;
                    ++cnt;
                }
        int ok = 1;
        while (cnt != 0) {
            int okk = 0;
            for (int i = 0; i < n; ++i)
                if (!okk && able[i] && v[i].second.first + O == 0) {
                    O = v[i].second.second;
                    able[i] = 0;
                    okk = 1;
                    --cnt;
                }
            if (!okk) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < n; ++i)
                if (mask & (1 << i))
                    if (v[i].second.second == 0)
                        if (v[i].second.first + O != 0)
                            ok = 0;
        }
        if (ok)
            ++ans;
    }
    cout << ans << '\n';
}

signed main() {
    cout << 57 + 100 + 54 + 0 + 10 << endl;
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    int t = 1; // cin >> t;
    while (t--)
        solve();
    return 0;
}
