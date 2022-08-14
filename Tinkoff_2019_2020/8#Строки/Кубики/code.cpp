#include <bits/stdc++.h>

using namespace std;

vector<int> zf(vector<int> &v) {
    vector<int> z(v.size());
    int l = 0, r = 0;
    for (int i = 1; i < v.size(); ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < v.size() && v[i + z[i]] == v[z[i]])
            ++z[i];
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}

int main () {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    for (int i = n - 1; i >= 0; --i)
        v.push_back(v[i]);
    v = zf(v);
    set<int> ans;
    for (int i = n; i < n + n; ++i) {
        if (i + v[i] == n + n && v[i] % 2 == 0)
            ans.insert(n - v[i] / 2);
    }
    ans.insert(n);
    for (auto x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}
