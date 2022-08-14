#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5000;

vector<int> g[MAXN];

bool res = false;

int col[MAXN];

void dfs(int v) {
    col[v] = 1;
    for (auto x : g[v]) {
        if (col[x] == 0)
            dfs(x);
        else if (col[x] == 1)
            res = 1;
    }
    col[v] = 2;
}

int main () {
    for (int i = 0; i < MAXN; ++i)
        col[i] = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j + i < n; ++j) {
            char t;
            cin >> t;
            if (t == 'R')
                g[i].push_back(i + j);
            else
                g[i + j].push_back(i);
        }
    }
    for(int i = 0; i < n; ++i)
        if (!col[i])
            dfs(i);
    if (res)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
