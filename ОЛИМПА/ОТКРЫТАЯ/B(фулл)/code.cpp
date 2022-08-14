#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int ans = (n * k + m - 1) / m;
    cout << ans << '\n';
    deque<int> perm;
    for (int i = 0; i < m; ++i)
        perm.push_back(i + 1);
    for (int id = 0; id < ans; ++id) {
        int beg = id * m % n;
        if (beg == 0) {
            perm.push_front(perm.back());
            perm.pop_back();
        }
        vector<int> ans(n);
        for (int i = 0; i < m; ++i)
            ans[(i + beg) % n] = perm[i];
        for (auto x : ans)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
