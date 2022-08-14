#include <bits/stdc++.h>

using namespace std;

const long long P = 100151, MOD = 1000000181;

const int MAXN = 100031;

int my_groop[MAXN], w[MAXN], sz[MAXN];

vector<int> g[MAXN];

map<pair<int, int>, int> meme, hashs;

int timer = 1;

long long pep[MAXN];

void dfs(int v, int p = -1) {
    sz[v] = 1;
    if (g[v].size() == 1 && p != -1) {
        if (hashs.find({sz[v], w[v]}) != hashs.end()) {
            ++meme[{sz[v], w[v]}];
            my_groop[v] = hashs[{sz[v], w[v]}];
            return;
        }
        my_groop[v] = timer++;
        hashs[{sz[v], w[v]}] = my_groop[v];
        meme[{sz[v], w[v]}] = 1;
        return;
    }
    for (auto x : g[v])
        if (x != p)
            dfs(x, v);
    vector<int> types;
    types.reserve(g[v].size() + 1);
    for (auto x : g[v])
        if (x != p) {
            types.push_back(my_groop[x]);
            sz[v] += sz[x];
        }
    sort(types.begin(), types.end());
    types.push_back(w[v]);
    int now_hash = 0;
    for (int i = 0; i < types.size(); ++i) {
        now_hash = ((long long)now_hash + (long long)types[i] * pep[i])% MOD;
    }
    types.clear();
    types.shrink_to_fit();
    if (hashs.find({sz[v], now_hash}) != hashs.end()) {
        ++meme[{sz[v], now_hash}];
        my_groop[v] = hashs[{sz[v], now_hash}];
        return;
    }
    meme[{sz[v], now_hash}] = 1;
    my_groop[v] = timer++;
    hashs[{sz[v], now_hash}] = my_groop[v];
}

int main () {
    pep[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        pep[i] = (pep[i - 1] * P) % MOD;
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> weights(n), w1(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
        w1[i] = weights[i];
    }
    sort(w1.begin(), w1.end());
    w1.resize(unique(w1.begin(), w1.end()) - w1.begin());
    map<int, int> cmprs;
    for (int i = 0; i < w1.size(); ++i)
        cmprs[w1[i]] = i + 1;
    w1.clear();
    w1.shrink_to_fit();
    for (int i = 0; i < n; ++i)
        w[i] = cmprs[weights[i]];
    cmprs.clear();
    weights.clear();
    weights.shrink_to_fit();
    dfs(0);
    long long ans = 0;
    for (auto x : meme) {
        //cout << x.first.first << " " << x.first.second << ": " << x.second << endl;
        ans += ((long long)x.second * (long long)(x.second - 1)) / 2ll;
    }
    cout << ans << '\n';
    return 0;
}
