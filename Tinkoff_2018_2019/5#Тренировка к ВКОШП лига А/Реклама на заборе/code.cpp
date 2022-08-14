#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> m >> n;
    vector<int> col(m);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        for (int j = l - 1; j < r; ++j) {
            col[j] = 1;
        }
    }
    int ans = 1;
    for (int i = 0; i < m; ++i) {
        ans &= col[i];
    }
    if (ans) {
       cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
