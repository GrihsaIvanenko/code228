#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int MAXN = 1e6;

bitset<(MAXN>>1)> b[2500];

char used[MAXN];

vector<pair<int, int>> g[MAXN];

pair<int, int> ans[MAXN];

bool can = true;

pair<int, int> dfs(int v, int left = 1) {
    pair<int, int> now = {left, !left};
    used[v] = 2 + left;
    for (auto x : g[v])
        if (!used[x.first]) {
            auto y = dfs(x.first, left ^ x.second);
            now.first += y.first;
            now.second += y.second;
        } else
            can &= (x.second == (used[v] ^ used[x.first]));
    return now;
}

void dfs1(int v, vector<int> &LL, vector<int>&RR, int left = 1) {
    used[v] = 1;
    if (left)
        LL.push_back(v);
    else
        RR.push_back(v);
    for (auto x : g[v])
        if (!used[x.first])
            dfs1(x.first, LL, RR, left ^ x.second);
}

int main() {
    memset(used, 0, sizeof(used));
    #ifndef DEBUG
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #else
        freopen("t.cpp", "r", stdin);
    #endif // DEBUG
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int t, p, q;
        cin >> t >> p >> q;
        --p;
        --q;
        g[p].push_back({q, t});
        g[q].push_back({p, t});
    }
    vector<pair<int, int>> tmp;
    for (int i = 0; i < n; ++i)
        if (!used[i])
            tmp.push_back(dfs(i));
    if (!can) {
        cout << "-1\n";
        return 0;
    }
    map<int, int> mm;
    int sm = 0;
    for (auto x : tmp) {
        ++mm[abs(x.first - x.second)];
        sm += abs(x.first - x.second);
    }
    vector<pair<int, int>> subs;
    for (auto x : mm) {
        int nw = 1;
        while (nw + nw - 1 < x.second) {
            subs.push_back({nw, x.first});
            nw += nw;
        }
        subs.push_back({x.second - nw + 1, x.first});
    }
    assert(subs.size() < 2500);
    b[0][0] = 1;
    for (int i = 0; i < subs.size(); ++i) {
        b[i + 1] = (b[i] | (b[i] << (subs[i].first * subs[i].second)));
    }
    int the_best = sm;
    for (int i = 0; i < sm; ++i)
        if (b[subs.size()][i])
            if (abs(i + i - sm) < abs(the_best + the_best - sm))
                the_best = i;
    multiset<int> L, R;
    int now = the_best;
    for (int i = subs.size(); i > 0; --i)
        if (b[i - 1][now]) {
            for (int j = 0; j < subs[i - 1].first; ++j)
                R.insert(subs[i - 1].second);
        } else {
            assert(now >= subs[i - 1].first * subs[i - 1].second);
            assert(b[i - 1][now - subs[i - 1].first * subs[i - 1].second]);
            for (int j = 0; j < subs[i - 1].first; ++j)
                L.insert(subs[i - 1].second);
            now -= subs[i - 1].first * subs[i - 1].second;
        }
    memset(used, 0, sizeof(used));
    bitset<MAXN> LLL;
    LLL.reset();
    for (int i = 0; i < n; ++i)
        if (!used[i]) {
            vector<int> LL, RR;
            dfs1(i, LL, RR);
            int c = abs(int(LL.size()) - int(RR.size()));
            if (L.find(c) != L.end()) {
                L.erase(L.find(c));
                if (LL.size() > RR.size())
                    for (auto x : LL)
                        LLL[x] = 1;
                else
                    for (auto x : RR)
                        LLL[x] = 1;
            } else {
                assert(R.find(c) != R.end());
                R.erase(R.find(c));
                if (LL.size() > RR.size())
                    for (auto x : RR)
                        LLL[x] = 1;
                else
                    for (auto x : LL)
                        LLL[x] = 1;
            }
        }
    int left_counter = 0;
    for (int i = 0; i < n; ++i)
        left_counter += LLL[i];
    int prob_size = max(left_counter, n - left_counter);
    vector<int> has = {2};
    for (int i = 3; 2 + int(has.size()) * int(has.size() - 1) < prob_size; ++i) {
        bool good = true;
        for (int j = 2; j * j <= i; ++j)
            if (i % j == 0)
                good = false;
        if (good)
            has.push_back(i);
    }
    int U1 = 0, U2 = 0;
    for (int i = 0; i < n; ++i) {
        if (LLL[i]) {
            if (U1 == 0)
                ans[i] = {0, -1};
            else if (U1 == 1)
                ans[i] = {0, 0};
            else {
                assert(has.size() > 1);
                int poln = (U1 - 2) / (has.size() - 1);
                int kus = (U1 - 2) % (has.size() - 1);
                if (kus >= poln)
                    ++kus;
                ans[i] = {poln, kus};
            }
            ++U1;
        } else {
            if (U2 == 0)
                ans[i] = {0, -1};
            else if (U2 == 1)
                ans[i] = {0, 0};
            else {
                assert(has.size() > 1);
                int poln = (U2 - 2) / (has.size() - 1);
                int kus = (U2 - 2) % (has.size() - 1);
                if (kus >= poln)
                    ++kus;
                ans[i] = {poln, kus};
            }
            ++U2;
        }
    }
    cout << has.size() + 1 << '\n';
    for (int i = 0; i < n; ++i)
        if (LLL[i]) {
            cout << "0 " << has[ans[i].first] << ' ';
            if (ans[i].second == -1)
                cout << "0\n";
            else
                cout << has[ans[i].second] << '\n';
        } else {
            cout << has[ans[i].first] << " 0 ";
            if (ans[i].second == -1)
                cout << "0\n";
            else
                cout << has[ans[i].second] << '\n';
        }
    return 0;
}
