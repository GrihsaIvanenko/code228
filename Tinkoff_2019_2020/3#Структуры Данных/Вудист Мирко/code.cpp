#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
tree<pair<ll, int>, null_type, less<pair<ll, int>>, rb_tree_tag, tree_order_statistics_node_update> s;

int main() {
    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    int P;
    cin >> P;
    for (int i = 0; i < n; ++i)
        v[i] -= P;
    for (int i = 1; i < n; ++i)
        v[i] += v[i - 1];
    long long ans = 0;
    s.insert({0, 0});
    for (int i = 0; i < n; ++i) {
        ans += (long long)(s.order_of_key({v[i], n + 1}));
        s.insert({v[i], i + 1});
    }
    cout << ans << '\n';
    return 0;
}
