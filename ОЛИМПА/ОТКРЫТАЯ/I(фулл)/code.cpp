#include <bits/stdc++.h>

using namespace std;

const int MAXC = 1e6 + 2;
const int MAXN = 1e5 + 2;

long long ANS = 0, ans[MAXC];

int now[MAXN], lp[MAXC], C[MAXN], a[MAXN], b[MAXN], p[MAXN], r[MAXN], sz[MAXN], used[MAXN];

vector<int> dels[MAXC], rebs[MAXC];

int get(int x) {
    if (p[x] == x)
        return x;
    return p[x] = get(p[x]);
}

void unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b)
        return;
    if (r[a] < r[b])
        swap(a, b);
    r[a] = max(r[a], r[b] + 1);
    p[a] = b;
    sz[b] += sz[a];
}

void calc(int num) {
    vector<pair<int, int>> fact;
    int tmp = num;
    while (tmp != 1) {
        if (!fact.size() || fact.back().first != lp[tmp])
            fact.push_back({lp[tmp], 0});
        ++fact.back().second;
        tmp /= lp[tmp];
    }
    queue<pair<int, int>> q;
    q.push({0, 1});
    while (q.size()) {
        pair<int, int> p = q.front();
        q.pop();
        if (p.first == fact.size()) {
            dels[num].push_back(p.second);
        } else {
            for (int i = 0; i <= fact[p.first].second; ++i) {
                q.push({p.first + 1, p.second});
                p.second *= fact[p.first].first;
           }
        }
    }
    sort(dels[num].rbegin(), dels[num].rend());
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a[i] >> b[i] >> C[i];
        --a[i];
        --b[i];
        rebs[C[i]].push_back(i);
    }
    for (int NOW = MAXC - 1; NOW > 0; --NOW) {
        if (!rebs[NOW].size())
            continue;
        calc(NOW);
        for (auto x : rebs[NOW])
            unite(a[x], b[x]);
        for (auto x : rebs[NOW]) {
            int tmp = get(a[x]);
            if (!used[tmp]) {
                used[tmp] = 1;
                ans[NOW] += (long long)sz[tmp] * (long long)(sz[tmp] - 1);
            }
        }
        for (auto x : rebs[NOW]) {
            p[a[x]] = a[x];
            p[b[x]] = b[x];
            sz[a[x]] = sz[b[x]] = 1;
            used[a[x]] = used[b[x]] = 0;
            ++now[x];
            if (now[x] < dels[C[x]].size())
                rebs[dels[C[x]][now[x]]].push_back(x);
        }
        rebs[NOW].clear();
        for (int i = 2; i * NOW < MAXC; ++i)
            ans[NOW] -= ans[i * NOW];
        ANS += ans[NOW] * (long long)NOW;
    }
    cout << ANS << '\n';
}

void precalc() {
    for (int i = 0; i < MAXN; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    vector<int> simple;
    for (int i = 2; i < MAXC; ++i) {
        if (!lp[i]) {
            simple.push_back(i);
            lp[i] = i;
        }
        for (int j = 0; j < simple.size() && simple[j] <= lp[i] && i * simple[j] < MAXC; ++j)
            lp[i * simple[j]] = simple[j];
    }
}

int main() {
    precalc();
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
