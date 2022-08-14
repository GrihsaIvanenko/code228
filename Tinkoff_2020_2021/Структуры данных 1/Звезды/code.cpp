#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 129;

int fenv[MAXN][MAXN][MAXN];

void add(int a, int b, int c, int l) {
    for (int i = a; i < MAXN; i += (i & -i))
        for (int j = b; j < MAXN; j += (j & -j))
            for (int k = c; k < MAXN; k += (k & -k))
                fenv[i][j][k] += l;
}

int sum(int a, int b, int c) {
    int ans = 0;
    for (int i = a; i > 0; i -= (i & -i))
        for (int j = b; j > 0; j -= (j & -j))
            for (int k = c; k > 0; k -= (k & -k))
                ans += fenv[i][j][k];
    return ans;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int m;
    cin >> m;
    while (m != 3) {
        if (m == 1) {
            int x, y, z, k;
            cin >> x >> y >> z >> k;
            ++x;
            ++y;
            ++z;
            add(x, y, z, k);
        } else {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            ++x2;
            ++y2;
            ++z2;
            cout << (ll)sum(x2, y2, z2) - (ll)sum(x1, y2, z2) - (ll)sum(x2, y1, z2) - (ll)sum(x2, y2, z1) +
            (ll)sum(x1, y1, z2) + (ll)sum(x1, y2, z1) + (ll)sum(x2, y1, z1) - (ll)sum(x1, y1, z1) << '\n';
        }
        cin >> m;
    }
    return 0;
}
