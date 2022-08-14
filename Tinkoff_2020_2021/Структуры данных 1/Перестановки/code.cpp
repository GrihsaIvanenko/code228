#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

vector<int> v[MAXN + MAXN];

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, Q;
    cin >> n >> Q;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v[i + MAXN].push_back(x);
    }
    for (int i = MAXN - 1; i > 0; --i)
        merge(v[i + i].begin(), v[i + i].end(), v[i + i + 1].begin(), v[i + i + 1].end(), back_inserter(v[i]));
    for (int q = 0; q < Q; ++q) {
        int x, y, k, l, ans = 0;
        cin >> x >> y >> k >> l;
        --x;
        x += MAXN;
        y += MAXN;
        while (x < y) {
            if (x & 1) {
                ans += upper_bound(v[x].begin(), v[x].end(), l) - lower_bound(v[x].begin(), v[x].end(), k);
                ++x;
            }
            if (y & 1) {
                --y;
                ans += upper_bound(v[y].begin(), v[y].end(), l) - lower_bound(v[y].begin(), v[y].end(), k);
            }
            x >>= 1;
            y >>= 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
