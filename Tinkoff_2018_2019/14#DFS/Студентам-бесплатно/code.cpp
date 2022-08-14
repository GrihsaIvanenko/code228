#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;

set<int> lg[MAXN], rg[MAXN];

vector<pair<int, int>> way;

void dfs(int v, int left = 1) {
    if (left) {
        while (!lg[v].empty()) {
            int to = *lg[v].begin();
            lg[v].erase(to);
            rg[to].erase(v);
            dfs(to, 0);
            way.push_back({v, to});
        }
    } else {
        while (!rg[v].empty()) {
            int to = *rg[v].begin();
            rg[v].erase(to);
            lg[to].erase(v);
            dfs(to, 1);
            way.push_back({to, v});
        }
    }
}

int main() {
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    map<pair<int, int>, int> input;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        input[{a, b}] = i;
        lg[a].insert(b);
        rg[b].insert(a);
    }
    for (int i = 0; i < n; ++i) {
        if (lg[i].size() % 2) {
            lg[i].insert(MAXN - 1);
            rg[MAXN - 1].insert(i);
        }
        if (rg[i].size() % 2) {
            rg[i].insert(MAXN - 1);
            lg[MAXN - 1].insert(i);
        }
    }
    if (lg[MAXN - 1].size() % 2) {
        lg[MAXN - 1].insert(MAXN - 1);
        rg[MAXN - 1].insert(MAXN - 1);
    }
    for (int i = 0; i < MAXN; ++i) {
        if (lg[i].size() != 0)
            dfs(i);
    }
    vector<char> ans(m);
    for (int i = 0; i < way.size(); ++i) {
        if (input.find(way[i]) != input.end()) {
            if (i % 2)
                ans[input[way[i]]] = 'W';
            else
                ans[input[way[i]]] = 'M';
        }
    }
    for (auto x : ans)
        cout << x;
    cout << '\n';
    return 0;
}
