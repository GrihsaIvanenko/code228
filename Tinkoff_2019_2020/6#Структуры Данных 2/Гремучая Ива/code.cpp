#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001, MAXUP = 21;

int up[MAXN][MAXUP], h[MAXN];

void up_h(int &a, int h) {
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h >= (1 << i)) {
            a = up[a][i];
            h -= (1 << i);
        }
}

int lca (int a, int b) {
    up_h(a, h[a] - min(h[a], h[b]));
    up_h(b, h[b] - min(h[a], h[b]));
    if (a == b)
        return a;
    for (int i = MAXUP - 1; i >= 0; --i)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

int way_length(int a, int b) {
    return h[a] + h[b] - 2 * h[lca(a, b)];
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXUP; ++i)
        up[0][i] = 0;
    h[0] = 0;
    int n;
    cin >> n;
    int d1 = 0, d2 = 0;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        --p;
        h[i] = h[p] + 1;
        up[i][0] = p;
        for (int j = 1; j < MAXUP; ++j)
            up[i][j] = up[up[i][j - 1]][j - 1];
        if (way_length(d1, i) > way_length(d1, d2)) {
            d2 = i;
        }
        if (way_length(i, d2) > way_length(d1, d2)) {
            d1 = i;
        }
        cout << way_length(d1, d2) << '\n';
    }
    return 0;
}
