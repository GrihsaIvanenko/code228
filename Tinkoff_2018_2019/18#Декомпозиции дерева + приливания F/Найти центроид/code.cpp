#include <bits/stdc++.h>

using namespace std;

const int maxn = 200000;

#define v go

int n;

vector<int> go[maxn], sizes[maxn];

int dfs(int x, int p){
    int ans = 1;
    for(int i = 0; i < go[x].size(); ++i)
        if(go[x][i] != p)
            sizes[x][i] =  dfs(go[x][i], x);
    for(int i = 0; i < go[x].size(); ++i)
        ans += sizes[x][i];
    return ans;
}

int dfs_centroid(int x, int anc = -1){
    for(int i = 0; i < v[x].size(); ++i)
        if(sizes[x][i] > (n>>1))
            return dfs_centroid(v[x][i], x);
    return x + 1;
}

int main(){
    cin >> n;
    //n_2 = n / 2;
    for(int i = 1; i < n; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        --a;
        --b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < v[i].size(); ++j)
            sizes[i].push_back(0);
    }
    dfs(0, -1);
    printf("%d", dfs_centroid(0));
    return 0;
}
