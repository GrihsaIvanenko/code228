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
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<vector<int>> v(n);
    for (int i = 0; i < n + n; ++i) {
        int x;
        cin >> x;
        v[x - 1].push_back(i);
    }
    vector<int> v1(n);
    for (int i = 0; i < n; ++i) {
        cin >> v1[i];
        --v1[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> v1[i];
        --v1[i];
    }
    int a1 = kolvo(v1, v);
    vector<int> v2(n);
    for (int i = 0; i < n; ++i) {
        cin >> v2[i];
        --v2[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> v2[i];
        --v2[i];
    }
    int a2 = kolvo(v2, v);
    if (a1 == a2)
        cout << "OK\n";
    else
        cout << "F\n my " << a1 << "; but correct is " << a2 << '\n';
}
