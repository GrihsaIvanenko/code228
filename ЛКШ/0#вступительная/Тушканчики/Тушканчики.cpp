#include <bits/stdc++.h>

using namespace std;

int pr[250000], push[250000], sizer[250000];

int t;

pair<int,int> get(int x){
    if(pr[x] == x)
        return {pr[x], push[x]};
    pair<int,int> ans = get(pr[x]);
    if(push[x] == -1)push[x] = ans.second;
    pr[x] = ans.first;
    return {pr[x], push[x]};
}

void unite(int a, int b, int cost){
    a = get(a).first, b = get(b).first;
    if(sizer[a] < sizer[b])
        swap(a, b);
    if(sizer[a] >= t && sizer[b] < t){
        push[b] = cost;
    }
    else if(sizer[a] < t && sizer[a] + sizer[b] >= t){
        push[a] = cost;
    }
    pr[b] = a;
    sizer[a] += sizer[b];
}


int main(){
    for(int i = 0; i < 250000; ++i){
        push[i] = -1;
        pr[i] = i;
        sizer[i] = 1;
    }
    int n, m;
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> t;
    vector<vector<int>> v(n, vector<int>(m));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
         cin >> v[i][j];
    vector<pair<int, pair<int,int>>> rebs;
    rebs.reserve(n * m * 2);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(i != n - 1)rebs.push_back({abs(v[i][j] - v[i + 1][j]), {i * 500 + j, i * 500 + 500 + j} });
            if(j != m - 1)rebs.push_back({abs(v[i][j] - v[i][j + 1]),{i * 500 + j, i * 500 + j + 1} });
        }
    }
    sort(rebs.begin(), rebs.end());
    for(int i = 0; i < rebs.size(); ++i){
        int cost = rebs[i].first, a = rebs[i].second.first, b = rebs[i].second.second;
        if(get(a).first != get(b).first){
            unite(a, b, cost);
        }
    }
    long long answer = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            get(i * 500 + j);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            long long tmp;
            cin >> tmp;
            answer += (tmp * (long long)push[(i * 500 + j)]);
        }
    }
    cout << answer << '\n';
    return 0;
}
