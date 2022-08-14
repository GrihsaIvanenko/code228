#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll solve(vector<int> &v) {
    if (v.size() == 1)
        return 0;
    vector<int> vl, vr;
    vl.reserve(v.size() / 2 + 1);
    vr.reserve(v.size() / 2 + 1);
    for (int i = 0; i < v.size(); ++i)
        if (i + i < v.size())
            vl.push_back(v[i]);
        else
            vr.push_back(v[i]);
    ll ans = solve(vl) + solve(vr);
    ll uk = 0;
    for (int i = 0; i < vl.size(); ++i) {
        while (uk < vr.size() && vr[uk] < vl[i])
            ++uk;
        ans += uk;
    }
    sort(v.begin(), v.end());
    return ans;
}

int main() {
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    cout << solve(v) << '\n';
    return 0;
}
