#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

vector<int> g[MAXN];

char used[MAXN];

int tin[MAXN], tup[MAXN], timer = 0;

set<int> ans;

set<pair<int, int>> cash;

void dfs(int v, int p) {
    used[v] = 1;
    tin[v] = tup[v] = timer++;
    int kids = 0;
    for (auto z : g[v]) {
        if (z == p) {
            continue;
        } else if (used[z]) {
            tup[v] = min(tup[v], tin[z]);
        } else {
            dfs(z, v);
            ++kids;
            if (tin[v] <= tup[z] && p != -1) {
                ans.insert(v);
            }
            tup[v] = min(tup[v], tup[z]);
        }
    }
    if (p == -1 && kids > 1) {
        ans.insert(v);
    }
}

void solve(){
    for (int i = 0; i < MAXN; ++i) {
        used[i] = 0;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        --c;
        int v = i + (MAXN>>1);
        g[a].push_back(v);
        g[b].push_back(v);
        g[c].push_back(v);
        g[v].push_back(a);
        g[v].push_back(b);
        g[v].push_back(c);
    }
    dfs(0, -1);
    vector<int> answer;
    for (auto x : ans) {
        if (x >= (MAXN>>1)) {
            answer.push_back(x - (MAXN>>1) + 1);
        }
    }
    cout << answer.size() << endl;
    for (auto x : answer) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    solve();
    return 0;
}

