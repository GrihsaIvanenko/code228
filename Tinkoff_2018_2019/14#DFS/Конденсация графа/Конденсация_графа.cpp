#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20000;

vector<int> g[MAXN], revg[MAXN];

int used[MAXN], ans[MAXN], number = 0;

vector<int> top_sort;

void dfs_top_sort(int it){
    used[it] = 1;
    for(int i = 0; i < g[it].size(); ++i)
        if(used[g[it][i] ] == 0)
            dfs_top_sort(g[it][i]);
    top_sort.push_back(it);
}

void dfs_make_ans(int it){
    used[it] = 2;
    ans[it] = number;
    for(int i = 0; i < revg[it].size(); ++i)
        if(used[revg[it][i] ] == 1)
            dfs_make_ans(revg[it][i]);
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
        revg[b].push_back(a);
    }
    for(int i = 0; i < n; ++i)
        if(used[i] == 0)
            dfs_top_sort(i);
    for(int i = n - 1; i > -1; --i){
        if(used[top_sort[i] ] == 1){
            ++number;
            dfs_make_ans(top_sort[i]);
        }
    }
    cout << number << endl;
    for(int i = 0; i < n; ++i)
        cout << ans[i] << " ";
}

int main(){
    solve();
    return 0;
}
