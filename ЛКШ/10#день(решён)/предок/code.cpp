#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

int tin[MAXN], tout[MAXN], timer = 0;

vector<int> g[MAXN];

void dfs(int v) {
    tin[v] = timer++;
    for (auto x : g[v]) {
        dfs(x);
    }
    tout[v] = timer++;
}

void solve() {
    int n, root = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        --t;
        if (t < 0) {
            root = i;
            continue;
        }
        g[t].push_back(i);
    }
    dfs(root);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (tin[a] <= tin[b] && tout[b] <= tout[a]) {
            cout << "1\n";
        } else{
            cout << "0\n";
        }
    }
}

int main() {
    solve();
    return 0;
}
