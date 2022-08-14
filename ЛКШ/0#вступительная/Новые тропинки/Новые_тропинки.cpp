#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000;

int used[maxn], comp[maxn], it = 0;

vector<int> g[maxn], revg[maxn], top_sort;

vector<long long> weight;

void dfs_top_sort(int v){
    used[v] = 1;
    for(int i = 0; i < g[v].size(); ++i)
        if(used[g[v][i] ] == 0)
            dfs_top_sort(g[v][i]);
    top_sort.push_back(v);
}

void dfs_make_comp(int v){
    used[v] = 2;
    comp[v] = it;
    for(int i = 0; i < revg[v].size(); ++i)
        if(used[revg[v][i] ] == 1)
            dfs_make_comp(revg[v][i]);
}

pair<int,int> calcul(int v){
    used[v] = 3;
    int ver = 1, reb = 0;
    for(int i = 0; i < revg[v].size(); ++i){
        if(comp[v] == comp[revg[v][i] ])
            ++reb;
        if(used[revg[v][i] ] == 2){
            pair<int,int> p = calcul(revg[v][i]);
            ver += p.first;
            reb += p.second;
        }
    }
    return {ver, reb};
}

long long get_weight(int v){
    pair<int,int> p = calcul(v);
    long long ans = p.first;
    ans *= (ans - 1);
    ans -= p.second;
    return ans;
}

long long dfs_mind_max_weight(int v){
    used[v] = 4;
    long long ans = weight[comp[v] ];
    for(int i = 0; i < g[v].size(); ++i){
        if(used[g[v][i] ] == 3)
            ans = max(ans, dfs_mind_max_weight(g[v][i]));
    }
    return ans;
}

int main(){
    int n, m;
    cin >> n >> m;
    set<pair<int,int>> ban;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        if(ban.find({a, b}) == ban.end()){
            ban.insert({a, b});
            --a;
            --b;
            g[a].push_back(b);
            revg[b].push_back(a);
        }
    }
    for(int i = 0; i < n; ++i)
        used[i] = false;
    for(int i = 0; i < n; ++i)
        if(used[i] == 0)
            dfs_top_sort(i);
    reverse(top_sort.begin(), top_sort.end());
    for(int i = 0; i < n; ++i){
        if(used[top_sort[i] ] == 1){
            dfs_make_comp(top_sort[i]);
            ++it;
        }
    }
    weight.resize(it);
    for(int i = 0; i < n; ++i){
        if(used[top_sort[i]] == 2){
            weight[comp[top_sort[i] ] ] = get_weight(top_sort[i]);
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; ++i)
        if(used[top_sort[i] ] == 3)
            ans += dfs_mind_max_weight(top_sort[i]);
    cout << ans << endl;
    return 0;
}
