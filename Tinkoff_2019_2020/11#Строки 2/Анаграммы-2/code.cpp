#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<long long> mods = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181},
ps = {100003, 100019, 100043, 100049, 100057, 100069, 100103, 100109, 100129, 100151};
const long long MAXN = 100111;
long long p[(int)10][(int)MAXN];
long long cnt[(int)MAXN];
int kolvo = 2;

signed main () {
    for (int i = 0; i < kolvo; ++i)
        p[i][0] = 1;
    cnt[0] = 0;
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 0; j < kolvo; ++j)
            p[j][i] = (p[j][i - 1] * ps[j]) % mods[j];
        cnt[i] = 0;
    }
    int n;
    cin >> n;
    vector<long long> v1(n);
    for (int i = 0; i < n; ++i)
        cin >> v1[i];
    vector<vector<set<long long>>> hss(kolvo, vector<set<long long>>(n));
    for (int i = 0; i < n; ++i) {
        vector<long long> hs(kolvo);
        for (int j = i; j < n; ++j) {
            for (int k = 0; k < kolvo; ++k)
                hs[k] = (hs[k]+ (mods[k]- cnt[v1[j]])* p[k][v1[j]])% mods[k];
            ++cnt[v1[j]];
            for (int k = 0; k < kolvo; ++k)
                hs[k] = (hs[k] + cnt[v1[j]] * p[k][v1[j]]) % mods[k];
            for (int k = 0; k < kolvo; ++k)
                hss[k][j - i].insert(hs[k]);
        }
        for (int j = n - 1; j >= i; --j)
            --cnt[v1[j]];
    }
    int m;
    cin >> m;
    vector<long long> v2(m);
    for (int i = 0; i < m; ++i)
        cin >> v2[i];
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        vector<long long> hs(kolvo);
        for (int j = i; j < m; ++j) {
            for (int k = 0; k < kolvo; ++k)
                hs[k] = (hs[k] + (mods[k] - cnt[v2[j]]) * p[k][v2[j]]) % mods[k];
            ++cnt[v2[j]];
            for (int k = 0; k < kolvo; ++k)
                hs[k] = (hs[k] + cnt[v2[j]] * p[k][v2[j]]) % mods[k];
            bool CAN = true;
            for (int k = 0; k < kolvo; ++k)
                if (hss[k][j - i].find(hs[k]) == hss[k][j - i].end())
                    CAN = false;
            if (CAN)
                ans = max(ans, j - i + 1);
        }
        for (int j = m - 1; j >= i; --j)
            --cnt[v2[j]];
    }
    cout << ans << '\n';
    return 0;
}
