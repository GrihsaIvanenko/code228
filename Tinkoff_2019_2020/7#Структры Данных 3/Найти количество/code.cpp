#include <bits/stdc++.h>

using namespace std;

int timer = 0;

const int MAXN = 300000;

vector<int> ans;

pair<int, map<int, int>> memory[MAXN];

vector<int> g[MAXN];

map<int, vector<pair<int, int>>> asks;

pair<int, int> dfs(int v) {
    int cur = -1, last_max = 0;
    int sz = 1;
    vector<int> ids(g[v].size());
    for (int i = 0; i < g[v].size(); ++i) {
        pair<int, int> p = dfs(g[v][i]);
        sz += p.first;
        ids[i] = p.second;
        if (cur == -1 || p.first > last_max) {
            cur = i;
            last_max = p.first;
        }
    }
    int pos;
    if (cur == -1) {
        pos = timer++;
        memory[pos].first = 0;
        memory[pos].second[0] = 1;
    } else {
        pos = ids[cur];
        ++memory[pos].first;
        ++memory[pos].second[-memory[pos].first];
        for (int i = 0; i < g[v].size(); ++i) {
            if (i == cur)
                continue;
            int now_id = ids[i];
            int add = memory[now_id].first, les = memory[pos].first;
            for (auto x : memory[now_id].second) {
                memory[pos].second[x.first + add - les + 1] += x.second;
            }
        }
    }
   for (auto x : asks[v])
        ans[x.second] = memory[pos].second[x.first - memory[pos].first];
    return {sz, pos};
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a;
        cin >> a;
        --a;
        g[a].push_back(i);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int v, d;
        cin >> v >> d;
        --v;
        asks[v].push_back({d, i});
    }
    ans.resize(q);
    dfs(0);
    for (auto x : ans)
        cout << x << '\n';
    return 0;
}
