#include <bits/stdc++.h>

using namespace std;

int gt(char a) {
    if (a == 'p')
        return 1;
    if (a == 'r')
        return 0;
    if (a == 's')
        return 2;
    assert(false);
    return -1;
}

int str(int x) {
    if (x == 0)
        return 1;
    if (x == 1)
        return 2;
    if (x == 2)
        return 0;
    assert(false);
    return -1;
}

int slab(int x) {
    if (x == 0)
        return 2;
    if (x == 1)
        return 0;
    if (x == 2)
        return 1;
    assert(false);
    return -1;
}

void solve2(string s) {
    int n = s.size();
    vector<vector<vector<vector<int>>>> dp(3, vector<vector<vector<int>>> (n, vector<vector<int>> (n + 1, vector<int> (2))));
    for (int i = 0; i < n; ++i)
        dp[gt(s[i])][i][i + 1][0] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len;
            for (int mid = l + 1; mid < r; ++mid) {
                for (int ktol = 0; ktol < 3; ++ktol) {
                    for (int ktor = 0; ktor < 3; ++ktor) {
                        for (int skokl = 0; skokl < 2; ++skokl) {
                            for (int skokr = 0; skokr < 2; ++skokr) {
                                if (dp[ktol][l][mid][skokl] && dp[ktor][mid][r][skokr]) {
                                    if (ktol == ktor) {
                                        dp[ktol][l][r][1] = 1;
                                    } else if (str(ktol) == ktor) {
                                        dp[ktor][l][r][skokr] = 1;
                                    } else if (str(ktor) == ktol) {
                                        dp[ktol][l][r][skokl] = 1;
                                    } else {
                                        assert(false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int ok = 1;
        int now = gt(s[i]);
        if (i != 0 && max(dp[slab(now)][0][i][0], dp[slab(now)][0][i][1]) == 0)
            ok = 0;
        if (i != n - 1 && max(dp[slab(now)][i + 1][n][0], dp[slab(now)][i + 1][n][1]) == 0)
            ok = 0;
        if (ok)
            cout << "1";
        else
            cout << "0";
    }
    cout << '\n';
}

void solve1(string s) {
    vector<int> l(3), r(3);
    for (auto x : s)
        ++r[gt(x)];
    for (int i = 0; i < s.size(); ++i) {
        int now = gt(s[i]);
        --r[now];
        int ok = 1;
        if (l[slab(now)] == 0 && l[str(now)] != 0)
            ok = 0;
        if (r[slab(now)] == 0 && r[str(now)] != 0)
            ok = 0;
        ++l[now];
        if (ok)
            cout << "1";
        else
            cout << "0";
    }
    cout << '\n';
}

void solve() {
    int d;
    cin >> d;
    string s;
    cin >> s;
    if (d == 1)
        solve1(s);
    else
        solve2(s);
}

signed main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    int t = 1; cin >> t;
    while (t--)
        solve();
    return 0;
}
