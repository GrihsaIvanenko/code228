#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

int pw[MAXN];

struct sparce{
    vector<vector<int>> sparce;
    void build(vector<int> &v) {
        sparce.resize(pw[v.size()] + 1);
        sparce[0] = v;
        for (int i = 1; i <= pw[v.size()]; ++i) {
            sparce[i].resize(v.size() - (1 << i) + 1);
            for (int j = 0; j < sparce[i].size(); ++j) {
                sparce[i][j] = min(sparce[i - 1][j], sparce[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int min_on_path(int l, int r) {
        if (l == r) return sparce[0][l];
        return min(sparce[pw[r - l + 1]][l], sparce[pw[r - l + 1]][r + 1 - (1 << pw[r - l + 1])]);
    }
};

int main() {
    freopen("sparse.in", "r", stdin);freopen("sparse.out", "w", stdout);
    for (int i = 3; i < MAXN; ++i) pw[i] = -1;
    for (int i = 0; i < 18; ++i) pw[1 << i] = i;
    for (int i = 3; i < MAXN; ++i) if (pw[i] == -1) pw[i] = pw[i - 1];
    int n, m, a1;
    cin >> n >> m >> a1;
    vector<int> v = {a1};
    v.reserve(n);
    for (int i = 1; i < n; ++i) {
        int tmp = (v.back() * 23 + 21563) % 16714589;
        v.push_back(tmp);
    }
    sparce sp;
    sp.build(v);
    int l, r;
    cin >> l >> r;
    for (int i = 1; i < m; ++i) {
        int res = sp.min_on_path(min(l, r) - 1, max(l, r) - 1);
        l = ((17 * l + 751 + res + i + i) % n) + 1;
        r = ((13 * r + 593 + res + i * 5) % n) + 1;
    }
    cout << l << " " << r << " " << sp.min_on_path(min(l, r) - 1, max(l, r) - 1) << '\n';
    return 0;
}
