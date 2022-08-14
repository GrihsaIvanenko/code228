#include <bits/stdc++.h>

using namespace std;

int kolvo(vector<int> &now, vector<vector<int>> &cnt) {
    int ans = 0, i = 0, n = cnt.size();
    for (auto x : now) {
        ans += abs(cnt[x][0] - i) + abs(cnt[x][1] - i - n);
        ++i;
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "a", stdout);
    int n;
    cin >> n;
    vector<vector<int>> v(n);
    for (int i = 0; i < n + n; ++i) {
        int x;
        cin >> x;
        v[x - 1].push_back(i);
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
        ans[i] = i;
    vector<int> now = ans;
    while (next_permutation(now.begin(), now.end())) {
        if (kolvo(now, v) < kolvo(ans, v))
            ans = now;
    }
    for (auto x : ans)
        cout << x + 1 << ' ';
    for (auto x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
}
