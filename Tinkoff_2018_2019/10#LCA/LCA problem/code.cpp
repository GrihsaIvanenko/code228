#include  <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> g[100000];
int  tin[100000], tout[100000];
int t = 0;

int up[100000][30];

void dfs (int v) {
    for (int l = 1; l < 30; l++)
        up[v][l] = up[up[v][l-1]][l-1];
    tin[v] = t++;
    for (int u : g[v]) {
        up[u][0] = v;
        dfs(u);
    }
    tout[v] = t++;
}

bool a (int u, int v) {
    return tin[u] <= tin[v] && tin[v] <= tout[u];
}


int lca (int v, int u) {
    if(v == u)return v;
    if (a(v, u)) return v;
    if (a(u, v)) return u;
    for (int l = 29; l >= 0; l--)
        if (!a(up[v][l], u))
            v = up[v][l];
    return up[v][0];
}

int32_t main(){
    int n, m, x;
    cin >> n >> m;
    for(int i = 1; i < n; ++i){
        cin >> x;
        g[x].push_back(i);
    }
    for(int i = 0; i < 30; ++i)up[0][i] = 0;
    dfs(0);
    /*for(int j = 0; j < 15; ++j){
        cout <<  " " << j << " " << tin[j] << " " << tout[j] << endl;
    }
    while(true){
        int b, c;
        cin >> b >> c;
        cout << lca(b, c) << endl;
        if(a(b, c))cout<<"LOL" << endl;
    }*/
    int ai[2 * m + 1], y, z, lastans;
    cin >> ai[1] >> ai[2] >> x >> y >> z;
    for(int i = 3; i < 2 * m + 1; ++i){
        ai[i] = ((long long)ai[i - 2] * x + (long long)ai[i - 1] * y + z) % n;
    }
    long long ans = 0;
    ans = lastans = lca(ai[1], ai[2]);
    //cout << ans << endl;
    for(int i = 2; i <= m; ++i){
        lastans = lca((lastans + ai[i * 2 - 1]) % n, ai[i * 2]);
        ans += lastans;
    }
    cout << ans << endl;
}
