#include <bits/stdc++.h>

using namespace std;

struct segtree{
    vector<int> pref, numbers;
    segtree() {}
};

vector<segtree> hell;

int sizer = 1;

int ans(int x, int y, int num, int v = 1, int lb = 0, int rb = sizer) {
    if (x >= rb || y <= lb || num == 0) {
        return 0;
    }
    if (x <= lb && rb <= y) {
        return num;
    }
    return ans(x, y, hell[v].pref[num - 1], v << 1, lb, (lb + rb) / 2) + ans(x, y, num - hell[v].pref[num - 1], (v << 1) + 1, (lb + rb) / 2, rb);
}

void solve() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (sizer < n) {
        sizer = sizer << 1;
    }
    hell.resize(sizer << 1);
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        hell[sizer + i].numbers.push_back(t);
        hell[sizer + i].pref.resize(1);
    }
    for (int i = sizer - 1; i > 0; --i) {
        hell[i].numbers.resize(hell[i << 1].numbers.size() + hell[(i << 1) + 1].numbers.size());
        merge(hell[i << 1].numbers.begin(), hell[i << 1].numbers.end(), hell[(i << 1) + 1].numbers.begin(), hell[(i << 1) + 1].numbers.end(), hell[i].numbers.begin());
        hell[i].pref.resize(hell[i].numbers.size());
        int it = 0;
        for (int j = 0; j < hell[i].numbers.size(); ++j) {
            if (j != 0) {
                hell[i].pref[j] = hell[i].pref[j - 1];
            }
            if (hell[i].numbers[j] == hell[i << 1].numbers[it]) {
                ++it;
                ++hell[i].pref[j];
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int x, y, k, l;
        cin >> x >> y >> k >> l;
        --x;
        --k;
        cout << ans(x, y, l) - ans(x, y, k) << '\n';
    }
}

int main() {
    solve();
    return 0;
}
