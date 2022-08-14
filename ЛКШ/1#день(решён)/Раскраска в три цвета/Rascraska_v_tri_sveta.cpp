#include <bits/stdc++.h>

using namespace std;

//#define push_back push_back

const int MAXN = 1000;

vector<int> g[MAXN << 1], revg[MAXN << 1], ts;

int used[MAXN << 1], id[MAXN << 1], timer = 0;

void dfs_ts(int v) {
    used[v] = 1;
    for (auto x : g[v]) {
        if (used[x] == 0) {
            dfs_ts(x);
        }
    }
    ts.push_back(v);
}

void dfs_id(int v) {
    used[v] = 2;
    id[v] = timer;
    for (auto x : revg[v]) {
        if (used[x] == 1) {
            dfs_id(x);
        }
    }
}

map<char, char> nex;

void solve() {
    nex['R'] = 'G';
    nex['G'] = 'B';
    nex['B'] = 'R';
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (s[a] == s[b]) {
           g[a << 1].push_back((b << 1) + 1);
           revg[(b << 1) + 1].push_back(a << 1);
           g[(a << 1) + 1].push_back((b << 1));
           revg[(b << 1)].push_back((a << 1) + 1);
           swap(a, b);
           g[a << 1].push_back((b << 1) + 1);
           revg[(b << 1) + 1].push_back(a << 1);
           g[(a << 1) + 1].push_back((b << 1));
           revg[(b << 1)].push_back((a << 1) + 1);
        }
        else {
            if (nex[s[b]] == s[a]) {
                swap(a, b);
            }
            g[a << 1].push_back(b << 1);
            revg[b << 1].push_back(a << 1);
            g[(b << 1) + 1].push_back((a << 1) + 1);
            revg[(a << 1) + 1].push_back((b << 1) + 1);
        }
    }
    /*for (int i = 0; i < (n << 1); ++i) {
        cout << i << " : ";
        for (auto x : g[i]) {
            cout << x << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < (n << 1); ++i) {
        used[i] = 0;
    }
    for (int i = 0; i < (n << 1); ++i) {
        if (used[i] == 0) {
            dfs_ts(i);
        }
    }
    reverse(ts.begin(), ts.end());
    /*for (auto x : ts) {
        cout << x << " ";
    }
    cout << "ts\n";*/
    for (int i = 0; i < (n << 1); ++i) {
        if (used[ts[i]] == 1) {
            dfs_id(ts[i]);
            ++timer;
        }
    }
    /*int i = 0;
     for (auto x : ts) {
        cout << id[i++] << " ";
    }
    cout << "id\n";*/
    bool gd = 1;
    for (int i = 0; i < n; ++i) {
        if (id[(i << 1) + 1] < id[i << 1]) {
            s[i] = nex[nex[s[i]]];
        }
        else if (id[(i << 1) + 1] > id[i << 1]) {
            s[i] = nex[s[i]];
        }
        else{
            gd = 0;
        }
    }
    if (gd) {
        cout << s << '\n';
    }
    else {
        cout << "Impossible\n";
    }
    return;
}

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    solve();
    return 0;
}
