#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;

vector<int> g[MAXN << 1], revg[MAXN << 1], ts;

char used[MAXN << 1];

int id[MAXN << 1], timer = 0;

void dfs_ts(int v) {
    used[v] = 1;
    for (auto x : g[v]) {
        if (used[x] == 0) {
            dfs_ts(x);
        }
    }
    ts.push_back(v);
}

void dfs_rev(int v) {
    id[v] = timer;
    used[v] = 2;
    for (auto x : revg[v]) {
        if (used[x] == 1) {
            dfs_rev(x);
        }
    }
}

int main() {
    for (int i = 0; i < MAXN * 2; ++i) {
        id[i] = 0;
        used[i] = 0;
    }
    int n;
    cin >> n;
    vector<int> ans(n);
    vector<int> col(n);
    for (int i = 0; i < n; ++i) {
        cin >> col[i];
    }
    vector<int> pos(n * 2);
    vector<int> p[MAXN];
    for (int i = 0; i < n * 2; ++i) {
        cin >> pos[i];
        --pos[i];
        p[pos[i]].push_back(i);
        if (i == 0 || pos[i - 1] == pos[i] || col[pos[i - 1]] != col[pos[i]]) {
           continue;
        }
        bool A = (p[pos[i - 1]].size() - 1);
        bool B = (p[pos[i]].size() - 1);
        g[pos[i - 1] * 2 + !A].push_back(pos[i] * 2 + B);
        revg[pos[i] * 2 + B].push_back(pos[i - 1] * 2 + !A);
        g[pos[i] * 2 + !B].push_back(pos[i - 1] * 2 + A);
        revg[pos[i - 1] * 2 + A].push_back(pos[i] * 2 + !B);
    }
    if (pos[n * 2 - 1] != pos[0] && col[pos[n * 2 - 1]] == col[pos[0]]) {
       bool A = 1;
       bool B = 0;
       g[pos[n * 2 - 1] * 2 + !A].push_back(pos[0] * 2 + B);
       revg[pos[0] * 2 + B].push_back(pos[n * 2 - 1] * 2 + !A);
       g[pos[0] * 2 + !B].push_back(pos[n * 2 - 1] * 2 + A);
       revg[pos[n * 2 - 1] * 2 + A].push_back(pos[0] * 2 + !B);
    }
    for (int i = 0; i < n * 2; ++i) {
        if (used[i] == 0) {
            dfs_ts(i);
        }
    }
    reverse(ts.begin(), ts.end());
    for (int i = 0; i < n * 2; ++i) {
        if (used[ts[i]] == 1) {
           dfs_rev(ts[i]);
           ++timer;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (id[i * 2] == id[i * 2 + 1]) {
            cout << "NO\n";
            return 0;
        }
        if (id[i * 2] > id[i * 2 + 1]) {
           ans[i] = 1;
        } else {
            ans[i] = 0;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i][ans[i]] + 1 << " ";
    }
    cout << endl;
    return 0;
}
