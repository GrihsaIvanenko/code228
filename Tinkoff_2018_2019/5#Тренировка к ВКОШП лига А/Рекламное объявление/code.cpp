#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    long long n, w, h;
    cin >> n >> w >> h;
    vector<pair<long long, long long>> words(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        words[i] = {a, b};
    }
    long double l = 0, r = 1e9+7;
    int tmp;
    for (int i = 0; i < 200; ++i) {
        bool can = true;
        long double mid = (l + r) / 2.0;
        long double ww = words[0].first * mid, hh = words[0].second * mid;
        if (ww > w) {
            can = 0;
        }
        if (hh > h) {
            can = 0;
        }
        for (int i = 1; i < n; ++i) {
            if (words[i - 1].second != words[i].second || (long double)words[i].first * mid + ww > w) {
                ww = (long double)words[i].first * mid;
                hh += (long double)words[i].second * mid;
            } else {
                ww += (long double)words[i].first * mid;
            }
            if (ww > w) {
                can = 0;
            }
            if (hh > h) {
                can = 0;
            }
        }
        if (can) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout.precision(10);
    cout << fixed << l << '\n';
    return 0;
}
