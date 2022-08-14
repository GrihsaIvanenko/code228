#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200002, MAXD = 19;

int oreo[MAXN][MAXD], max_[MAXN][MAXD], level[MAXN];

void solve() {
    level[1] = 0;
    for (int i = 2; i < MAXN; ++i)
        level[i] = level[i / 2] + 1;
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        oreo[i][0] = v[i];
        max_[i][0] = v[i];
    }
    for (int i = n; i < MAXN; ++i) {
        max_[i][0] = 0;
        oreo[i][0] = 0;
    }
    for (int j = 1; j < MAXD; ++j)
        for (int i = 0; i + (1 << j) <= MAXN; ++i) {
            oreo[i][j] = oreo[i][j - 1] | oreo[i + (1 << (j - 1))][j - 1];
            max_[i][j] = max(max_[i][j - 1], max_[i + (1 << (j - 1))][j - 1]);
        }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int val = v[i];
        for (int pos_ = i; pos_ < n;) {
            int lb = pos_, rb = n;
            for (int mid = (lb + rb) / 2; rb - lb > 1; mid = (lb + rb) / 2)
                if ((oreo[i][level[mid + 1 - i]] | oreo[mid + 1 - (1 << level[mid + 1 - i])][level[mid + 1 - i]]) == val)
                    lb = mid;
                else
                    rb = mid;
            int lb1 = pos_, rb1 = rb;
            for (int mid = (lb1 + rb1) / 2; rb1 - lb1 > 1; mid = (lb1 + rb1) / 2)
                if (max(max_[i][level[mid + 1 - i]], max_[mid + 1 - (1 << level[mid + 1 - i])][level[mid + 1 - i]]) < val)
                    lb1 = mid;
                else
                    rb1 = mid;
            if (max(max_[i][level[rb1 - i]], max_[rb1 - (1 << level[rb1 - i])][level[rb1 - i]]) == val)
                --rb1;
            ans += (long long)(rb1 - pos_);
            val = (oreo[i][level[rb - i + 1]] | oreo[rb + 1 - (1 << level[rb - i + 1])][level[rb - i + 1]]);
            pos_ = rb;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
