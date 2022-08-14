#include <bits/stdc++.h>

using namespace std;


int main() {
    int k = 89;
    vector<pair<int, int>> v(k, {-1, -1});
    int n;
    cin >> n;
    int sum = 0;
    pair<int, int> ans = {-1, -1};
    v[0] = {0, 0};
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sum += x;
        if (v[sum % k].first != -1) {
            if (ans.first < sum - v[sum % k].first ||
                ans.first == sum - v[sum % k].first && ans.second > i - v[sum % k].second + 1)
                    ans = {sum - v[sum % k].first, i - v[sum % k].second + 1};
        }
        if (v[sum % k].first == -1 || v[sum % k].first >= sum)
            v[sum % k] = {sum, i};
    }
    cout << ans.first << " -sum; " << ans.second << " -len" << endl;
    return 0;
}
