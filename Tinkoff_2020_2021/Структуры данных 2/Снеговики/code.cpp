#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> has = {make_pair(0, 0)};
    has.reserve(n + 1);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int p, x;
        cin >> p >> x;
        if (x > 0) {
            has.push_back({has[p].first + x, p});
        } else {
            has.push_back(has[has[p].second]);
        }
        ans += has.back().first;
    }
    cout << ans << '\n';
    return 0;
}
