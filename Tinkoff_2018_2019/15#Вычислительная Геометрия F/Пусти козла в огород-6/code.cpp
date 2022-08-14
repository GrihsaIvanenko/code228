#include <bits/stdc++.h>

using namespace std;

using ld = long double;

#define x first
#define y second

ld dust(pair<ld, ld> &A, pair<ld, ld> &B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main() {
    freopen("goat6.in", "r", stdin);
    freopen("goat6.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<ld, ld>> pt(n);
    for (int i = 0; i < n; ++i)
        cin >> pt[i].first >> pt[i].second;
    vector<ld> cur_dust(n, 1000000000.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                cur_dust[i] = min(cur_dust[i], dust(pt[i], pt[j]));
    cout.precision(10);
    ld ans = 0, mex = 50.0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            ld A = cur_dust[i], B = cur_dust[j], C = dust(pt[i], pt[j]), cur = 0;
            if (C < 2.0 || A < 1.0 || B < 1.0)
                continue;
            A = min(A, mex);
            B = min(B, mex);
            if (A + B <= C)
                cur = cur_dust[i] * cur_dust[i] + cur_dust[j] * cur_dust[j];
            else {
                ld Bmax = min(B, C - 1), Amax = min(A, C - 1);
                cur = max(Bmax * Bmax + (C - Bmax) * (C - Bmax), Amax * Amax + (C - Amax) * (C - Amax));
            }
            ans = max(ans, cur);
        }
    cout.precision(11);
    cout << fixed << ans * 3.14159265358 << endl;
}
