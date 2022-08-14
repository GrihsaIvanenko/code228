#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000, mod = 1e9+7;

vector<int> g[MAXN];

set<pair<int,int>> bridge;

int tin[MAXN], tup[MAXN], used[MAXN], timer = 0;

void dfs(int it, int p){
    used[it] = 1;
    tin[it]= tup[it] = timer++;
    for(int i = 0; i < g[it].size(); ++i){
        int to = g[it][i];
        if(to == p)
            continue;
        if(used[to])
            tup[it] = min(tup[it], tin[to]);
        else{
            dfs(to, it);
            tup[it] = min(tup[it], tup[to]);
            if(tup[to] > tin[it])
                bridge.insert({min(to, it), max(to, it)});
        }
    }
}

pair<int,int> dfs_count(int it){
    used[it] = 2;
    pair<int,int> ans = {0, 1};
    for(int i = 0; i < g[it].size(); ++i){
            if(bridge.find({min(it, g[it][i]), max(it, g[it][i])}) == bridge.end()){
                pair<int,int> now = {0, 0};
                if(used[g[it][i]] == 1)
                    now = dfs_count(g[it][i]);
                ans.first += now.first;
                ans.second += now.second;
            }
            else
                ans.first++;
    }
    return ans;
}

void solve(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        used[i] = 0;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1);
    int ans = 0;
    long long kolvo = 1;
    for(int i = 0; i < n; ++i)
        if(used[i] == 1){
            pair<int,int> mem = dfs_count(i);
            if(mem.first < 2){
                long long tmp = mem.second;
                kolvo *= tmp;
                kolvo %= mod;
                ++ans;
            }
        }
    cout << ans << " " << kolvo << endl;
}

int main(){
    solve();
    return 0;
}
