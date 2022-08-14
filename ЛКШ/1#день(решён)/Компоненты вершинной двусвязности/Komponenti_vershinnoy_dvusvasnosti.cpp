#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int MAXN = 20000, MAXR = 200000;

vector<pair<int, int>> g[MAXN];

int tin[MAXN], tup[MAXN], num[MAXR], cop[MAXR], timer = 0, cmp_timer = 1;

char used[MAXN], BAN[MAXR];

vector<int> went;

map<pair<int, int>, int> mm;

void dfs(int v, int p) {
    used[v] = 1;
    tin[v] = tup[v] = timer++;
    for (size_t i = 0; i < g[v].size(); ++i) {
        if (p != -1) {
            if (g[v][i].x == p) {
                continue;
            } else if (used[g[v][i].x ]) {
                tup[v] = min(tup[v], tin[g[v][i].x]);
                went.push_back(g[v][i].y);
            } else {
                int tmp = went.size();
                went.push_back(g[v][i].y);
                dfs(g[v][i].x, v);
                if (tup[g[v][i].x] >= tin[v]) {
                    for (size_t i = tmp; i < went.size(); ++i) {
                        if (BAN[went[i]] == 0) {
                            num[went[i]] = cmp_timer;
                            BAN[went[i]] = 1;
                        }
                    }
                    cmp_timer++;
                    went.resize(tmp);
                }
                tup[v] = min(tup[v], tup[g[v][i].x ]);
            }
        } else if (p == -1 && used[g[v][i].x] == 0) {
            went.push_back(g[v][i].y);
            dfs(g[v][i].x, v);
            for (size_t i = 0; i < went.size(); ++i) {
                if (BAN[went[i]] == 0) {
                    num[went[i]] = cmp_timer;
                    BAN[went[i]] = 1;
                }
            }
            cmp_timer++;
            went.resize(0);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < MAXR; ++i) {
        cop[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (mm.find({min(a, b), max(a, b)}) == mm.end()){
            g[a].push_back({b, i});
            g[b].push_back({a, i});
            mm[{min(a, b), max(a, b)}] = i;
            cop[i] = i;
        }
        else{
            cop[i] = mm[{min(a, b), max(a, b)}];
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        used[i] = 0;
    }
    for (int i = 0; i < MAXR; ++i) {
        BAN[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    cout << cmp_timer - 1 << endl;
    for (int i = 0; i < m; ++i) {
        cout << num[cop[i]] << " ";
    }
    cout << endl;
}

int main(){
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
    solve();
    return 0;
}
