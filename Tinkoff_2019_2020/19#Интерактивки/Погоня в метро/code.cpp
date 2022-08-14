#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n, k, q;
    cin >> n >> k >> q;
    ll cur_l = 0, cur_r = n;
    ll prev = n + 1;
    srand(time(nullptr));
    while (true) {
        while (cur_r - cur_l < prev) {
            prev = cur_r - cur_l;
            ll mid = (cur_l + cur_r + 1) / 2;
            cout << cur_l + 1 << ' ' << mid << endl;
            string res;
            cin >> res;
            if (res == "Yes") {
                if (cur_l + 1 == mid) {
                    return;
                }
                cur_l = max(cur_l - k, 0ll);
                cur_r = min(mid + k, n);
            } else {
                cur_l = max(mid - k, 0ll);
                cur_r = min(cur_r + k, n);
            }
        }
        ll tmp = rand() % (cur_r - cur_l);
        cout << tmp + cur_l + 1 << " " << tmp + cur_l + 1 << endl;
        string res;
        cin >> res;
        if (res == "Yes") {
            return;
        } else {
            cur_l = max(cur_l - k, 0ll);
            cur_r = min(cur_r + k, n);
            prev = cur_r - cur_l + 1;
        }
    }
}

#define DEBUGs
signed main() {
    #ifdef DEBUG
        freopen("test.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    int t = 1;//cin >> t;
    while (t--)
        solve();
    return 0;
}
