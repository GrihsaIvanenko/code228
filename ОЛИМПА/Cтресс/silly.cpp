//
// Created by grigo on 23.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define  x first
#define  y second
#define  int long long

bool cmp(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < a.size(); ++i)
        if (a[i] != b[i])
        return a[i] < b[i];
    return true;
}

void solve() {
    int n;
    cin >> n;
    deque<int> v;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    v.push_back(0);
    ++n;
    vector<vector<int>> kekw;
    for (int i = 0; i < n; ++i) {
        vector<int> v1;
        for (auto x : v)
            v1.push_back(x);
        kekw.push_back(v1);
        int tmp = v.back();
        v.pop_back();
        v.push_front(tmp);
    }
    cout << n - 1 << '\n';
    sort(kekw.begin(), kekw.end(), cmp);
    for (auto x : kekw) {
        cout << x.back() << " ";
    }
    cout << '\n';
}


signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
#endif
    int t = 1;// cin >> t;
    while (t--)
        solve();
    return 0;
}
