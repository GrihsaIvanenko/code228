#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> v(n);
    int last = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.rbegin(), v.rend());
    ans = v[0];
    for (int i = 1; i < n; ++i) {
        if (v[i] != v[i - 1]) {
            last = i;
        }
         ans += max(v[i] - last, 0ll);
    }
    cout << ans << endl;
    return 0;
}
