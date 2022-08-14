#include <bits/stdc++.h>

using namespace std;

bool online(pair<int, int> &a, pair<int, int> &b, pair<int, int> &c) {
    long long dx1 = c.first - a.first;
    long long dy1 = c.second - a.second;
    long long dx2 = b.first - a.first;
    long long dy2 = b.second - a.second;
    return ((dx1 * dy2 - dy1 * dx2) == 0);
}

bool solve(vector<pair<int, int>> v, int k, vector<pair<pair<int, int>, pair<int, int>>> &ans) {
    if (v.size() == 0)
        return true;
    if (k == 0)
        return false;
    if (v.size() == 1) {
        ans.push_back({v[0], {v[0].first + 1, v[0].second}});
        return true;
    }
    int n = v.size();
    if (n > k * k) {
        int SZ = min(n, k * k + 2);
        for (int i = 0; i < SZ; ++i)
            for (int j = i + 1; j < SZ; ++j) {
                int cnt = 0;
                for (int l = 0; l < n; ++l)
                    cnt += online(v[l], v[i], v[j]);
                if (cnt > k) {
                    vector<pair<int, int>> v1;
                    for (int l = 0; l < v.size(); ++l)
                        if (!online(v[l], v[i], v[j]))
                            v1.push_back(v[l]);
                    random_shuffle(v1.begin(), v1.end());
                    ans.push_back({v[i], v[j]});
                    bool res = solve(v1, k - 1, ans);
                    if (!res)
                        ans.pop_back();
                    return res;
                }
            }
        return false;
    }
    int SZ1 = min(k, n);
    int SZ2 = min(k + 1, n);
    for (int i = 0; i < SZ1; ++i)
        for (int j = i + 1; j < SZ2; ++j) {
            ans.push_back({v[i], v[j]});
            vector<pair<int, int>> v1;
            for (int l = 0; l < n; ++l)
                if (!online(v[l], v[i], v[j]))
                    v1.push_back(v[l]);
            random_shuffle(v1.begin(), v1.end());
            bool gg = solve(v1, k - 1, ans);
            if (gg)
                return gg;
            ans.pop_back();
        }
    return false;
}

int main() {
    srand(time(nullptr));
    // freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> v(n);
        vector<pair<pair<int, int>, pair<int, int>>> ans;
        for (int i = 0; i < n; ++i)
            cin >> v[i].first >> v[i].second;
        random_shuffle(v.begin(), v.end());
        bool gg = solve(v, k, ans);
        if (gg) {
            cout << "Yes\n" << ans.size() << '\n';
            for (auto x : ans)
                cout << x.first.first << " " << x.first.second << " " << x.second.first << " " << x.second.second << '\n';
        } else {
            cout << "No\n";
        }
    }
    return 0;
    return 1;
}
