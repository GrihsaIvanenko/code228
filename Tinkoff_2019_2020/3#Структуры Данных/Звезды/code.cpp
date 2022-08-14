#include <bits/stdc++.h>

using namespace std;

const int MAXN = 129;

long long fenv[MAXN][MAXN][MAXN];

void add(int n, int x1, int y1, int z1, long long inc) {
    for (int i = x1; i <= n; i += (i & -i))
        for (int j = y1; j <= n; j += (j & -j))
            for (int k = z1; k <= n; k += (k & -k))
                fenv[i][j][k] += inc;
}

long long get(int x1, int y1, int z1) {
    int ans = 0;
    for (int i = x1; i > 0; i -= (i & -i))
        for (int j = y1; j > 0; j -= (j & -j))
            for (int k = z1; k > 0; k -= (k & -k))
                ans += fenv[i][j][k];
    return ans;
}

long long sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    long long ans = get(x2, y2, z2);
    ans -= get(x1, y2, z2);
    ans -= get(x2, y1, z2);
    ans -= get(x2, y2, z1);
    ans += get(x1, y1, z2);
    ans += get(x1, y2, z1);
    ans += get(x2, y1, z1);
    ans -= get(x1, y1, z1);
    return ans;
}

int main(){
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            for (int k = 0; k < MAXN; ++k)
                fenv[i][j][k] = 0;
    int n;
    cin >> n;
    int k = 1;
    while (k != 3) {
        cin >> k;
        if (k == 1) {
            int a, b, c;
            long long k;
            cin >> a >> b >> c >> k;
            add(n, a + 1, b + 1, c + 1, k);
        } else if (k == 2) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << sum(x1, y1, z1, x2 + 1, y2 + 1, z2 + 1) << '\n';
        }
    }
    return 0;
}
