#include <bits/stdc++.h>

using namespace std;

vector<int> pr;

int get (int x)
{
    return (x == pr[x]) ? x : (pr[x] = get (pr[x]));
}

void unite (int x, int y)
{
    x = get (x);
    y = get (y);
    if(x == y)
    {
        return;
    }
    if (x < y)
    {
        swap (x, y);
    }
    pr[x] = y;
}

int main()
{

    int n, m;
    cin >> n >> m;
     pr.resize(n);
    for(int i = 0;i < n; ++i){
        pr[i] = i;
    }
    vector<pair<int,pair<int,int>>> v;
    for(int i = 0; i < m; ++i)
    {
        int a, b, cost;
        cin >> a >> b >> cost;
        a--;
        b--;
        v.push_back({cost,{a, b}});
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0;i < m;++i){
         if(get(v[i].second.first) != get(v[i].second.second)){
            unite(v[i].second.first, v[i].second.second);
            ans += v[i].first;
         }
    }
    cout << ans;
    return 0;
}


