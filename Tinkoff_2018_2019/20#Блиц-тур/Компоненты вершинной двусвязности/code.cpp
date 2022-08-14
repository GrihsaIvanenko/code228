#include <bits/stdc++.h>

using namespace std;

const int maxn = 20000;

int timer = 0, used[maxn], tin[maxn], fup[maxn], color[maxn];

vector<pair<int,short>> g[maxn];

void dfs(int v, int p = -1){
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for(int i = 0; i < g[v].size(); ++i){
        if(g[v][i].first == p)continue;
        if(used[g[v][i].first ])fup[v] = min(fup[v], tin[g[v][i].first ]);
        else {
            dfs(g[v][i].first, v);
            fup[v] = min(fup[v], fup[g[v][i].first ]);
            if(tin[v] < fup[g[v][i].first ]){
                g[v][i].second = max(g[v][i].second, (short)1);
                int to = g[v][i].first;
                for(int j = 0; j < g[to].size(); ++j){
                    if(g[to][j].first == v){
                        g[to][j].second = max(g[to][j].second, (short)1);
                    }
                }
            }
        }
    }
}

int ans = 1;

void dfs1(int x){
    used[x] = 0;
    color[x] = ans;
    for(int i = 0; i < g[x].size(); ++i){
        if(used[g[x][i].first ]){
            if(g[x][i].second % 2 == 0){
                dfs1(g[x][i].first);
            }
        }
    }
}

int main(){
   freopen("bicone.in", "r", stdin);
   freopen("bicone.out", "w", stdout);
    for(int i = 0; i < maxn; ++i)used[i] = 0;
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> reb(m);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        reb[i] = {min(a, b), max(a, b)};
    }
    sort(reb.begin(), reb.end());
    for(int i = 0; i < m; ++i){
        int a = reb[i].first, b = reb[i].second;
        if(g[a].size() == 0 || g[a].back().first != b){
            g[a].push_back({b, 0});
            g[b].push_back({a, 0});
        }
        else{
            g[a][g[a].size() - 1 ].second = 2;
            g[b][g[b].size() - 1 ].second = 2;
        }
    }
    for(int i = 0; i < n; ++i){
        if(!used[i])
            dfs(i);
    }
    for(int i = 0; i < n; ++i){
        if(used[i] == 1){
            dfs1(i);
            ++ans;
        }
    }
    cout << ans - 1 << endl;
    for(int i = 0; i < n; ++i)
        cout << color[i] << " ";
    cout << endl;
   return 0;
}
