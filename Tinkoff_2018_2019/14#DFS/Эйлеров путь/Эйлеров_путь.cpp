#include <bits/stdc++.h>

using namespace std;

const long long MAXn = 100002;

const int MAXN = 100000;

multiset<int> g[MAXN];

vector<pair<int,int>> ans;

void dfs(int it, int p){
    while(!g[it].empty()){
        int to = *g[it].begin();
        g[it].erase(g[it].find(to));
        g[to].erase(g[to].find(it));
        dfs(to, it);
    }
    ans.push_back({it, p});
}

void solve(){
    int n, start = 0;
    cin >> n;
    unordered_map<long long, int> was;
    for(long long i = 0; i < n; ++i){
        int t;
        cin >> t;
        if(t % 2)
            start = i;
        for(int j = 0; j < t; ++j){
            long long x;
            cin >> x;
            --x;
            if(was[min(i, x) * MAXn + max(i, x)] == 1)
                was[min(i, x) * MAXn + max(i, x)] = 0;
            else{
                g[x].insert(i);
                g[i].insert(x);
                was[min(i, x) * MAXn + max(i, x)] = 1;
            }
        }
    }
    ans.reserve(300000);
    dfs(start, -1);
    reverse(ans.begin(), ans.end());
    cout << ans.size() - 1 << endl;
    for(auto x : ans){
        cout << x.first + 1 << " ";
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    solve();
    return 0;
}
