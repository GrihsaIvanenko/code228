#include <bits/stdc++.h>

using namespace std;

const int maxn = 20000, INF = 1e9 + 6;

vector<pair<int,int>> g[maxn], revg[maxn];

int n;

void dikstra(int start, bool rev, vector<int> &ans){
    priority_queue<pair<int,int>> dust;
	dust.push({0, start});
    ans.assign(n, INF);
    while(!dust.empty()){
        int cost = -dust.top().first, to = dust.top().second;
        dust.pop();
        if(cost > ans[to])continue;
        ans[to] = cost;
        if(!rev){
            for(int i = 0; i < g[to].size(); ++i){
                if(ans[g[to][i].second ] > ans[to] + g[to][i].first){
                    ans[g[to][i].second] = ans[to] + g[to][i].first;
                    dust.push({-ans[g[to][i].second], g[to][i].second});
                }
            }
        }
        else{
            for(int i = 0; i < revg[to].size(); ++i){
                if(ans[revg[to][i].second ] > ans[to] + revg[to][i].first){
                    ans[revg[to][i].second] = ans[to] + revg[to][i].first;
                    dust.push({-ans[revg[to][i].second], revg[to][i].second});
                }
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int m, k, q;
    cin >> n >> m >> k >> q;
    for(int i = 0; i < m; ++i){
        int a, b, cost;
        cin >> a >> b >> cost;
        --a;
        --b;
        g[a].push_back({cost, b});
        revg[b].push_back({cost, a});
    }
    vector<int> hub(k);
    for(int i = 0; i < k; ++i){
        cin >> hub[i];
        --hub[i];
    }
    vector<int> dust_to[k], dust_from[k];
    for(int i = 0; i < k; ++i){
        dikstra(hub[i], 0, dust_to[i]);
        dikstra(hub[i], 1, dust_from[i]);
    }
    int ans_kolvo = 0;
    long long ans_cost = 0;
    for(int i = 0;i < q; ++i){
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int ans = INF * 2;
        for(int j = 0; j < k; ++j){
            ans = min(ans, dust_from[j][a] + dust_to[j][b]);
        }
        if(ans < INF){
            ++ans_kolvo;
            ans_cost += ans;
        }
    }
    cout << ans_kolvo << '\n' << ans_cost << '\n';
    return 0;
}
