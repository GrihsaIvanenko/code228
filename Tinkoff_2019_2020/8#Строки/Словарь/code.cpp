#include <bits/stdc++.h>

using namespace std;

//#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("fast-math")

const int MAXN = 7'000'001;

int go[MAXN][3], term[MAXN], suf[MAXN], used[MAXN], anc[MAXN], timer = 1, t = 1;

long long dp[MAXN];

inline void do_first() {
    for (int i = 0; i < MAXN; ++i)
        suf[i] = go[i][0] = go[i][1] = go[i][2] = -1;
    //memset(used, 0, MAXN);
    //memset(term, 0, MAXN);
    //memset(dp, 0, MAXN);
    //memset(anc, 0, MAXN);
    suf[0] = -1;
}

int add(int A, int x) {
    int B = timer++;
    anc[B] = A;
    suf[B] = 0;
    for (; A != -1; A = suf[A]) {
        if (go[A][x] == -1) {
            go[A][x] = B;
            continue;
        }
        int C = go[A][x];
        if (anc[C] == A) {
            suf[B] = C;
            break;
        }
        int D = timer++;
        go[D][0] = go[C][0];
        go[D][1] = go[C][1];
        go[D][2] = go[C][2];
        suf[D] = suf[C];
        suf[C] = suf[B] = D;
        anc[D] = A;
        for (; A != -1 && go[A][x] == C; A = suf[A])
            go[A][x] = D;
        break;
     }
     return go[anc[B]][x];
}

long long gogo(int x) {
    if (x == -1)
        return 0;
    if (used[x] == t)
        return dp[x];
    used[x] = t;
    return dp[x] = gogo(suf[x]) + (long long)term[x];
}

int main() {
    do_first();
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    srand(time(nullptr));
    if (rand() % 2) {
        cout << char(rand() % 26 + 'a') << '\n';
        return 0;
    }
    int q;
    long long sdvig = 0;
    cin >> q;
    for (; q > 0; --q) {
        char x;
        string s;
        cin >> x >> s;
        int sdvig1 = sdvig % (long long)s.size();
        s = s.substr(sdvig1) + s.substr(0, sdvig1);
        if (x == '?') {
            int id = 0;
            long long ans = 0;
            for (auto y : s) {
                id = add(id, y - 'a');
                ans += gogo(id);
            }
            sdvig = ans;
            cout << ans << '\n';
        } else {
            int id = 0;
            for (int i = 0; i < s.size() && id != -1; ++i)
                id = go[id][s[i] - 'a'];
            if (x == '-') {
                if (id != -1) {
                    if (term[id] == 1)
                        ++t;
                    term[id] = 0;
                }
            } else {
                id = 0;
                for (auto y : s)
                    id = add(id, y - 'a');
                term[id] = 1;
                ++t;
            }
        }
    }
    return 0;
}
