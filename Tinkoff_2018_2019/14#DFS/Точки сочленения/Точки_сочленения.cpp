#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

set<int> ans; int tin[MAXN], fup[MAXN];

vector<int> v[MAXN];bitset<MAXN> used;

int timer = 0;

void dfs(int anc, int x){
    tin[x] = fup[x] = timer++;used[x] = true;int kids = 0;
    for(auto y : v[x]){
        if(y == anc)continue;
        if(!used[y]){dfs(x, y);kids++;fup[x] = min(fup[x], fup[y]);if (fup[y] >= tin[x] && anc != -1){ans.insert(x);}}
        else fup[x] = min(fup[x], tin[y]);
    }
    if(anc== -1 && kids > 1)ans.insert(x);
}

int main(){
    int n, m;
    used.reset();
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int x, y;
        cin >> x >> y;
        x--;y--;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i = 0; i < n; ++i)if(!used[i])dfs(-1, i);
    cout << ans.size() << endl;
    for(auto x : ans)cout << x + 1 << " ";
    return 0;
}
