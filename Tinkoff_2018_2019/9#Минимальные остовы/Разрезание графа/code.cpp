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
    //freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
    }
    pr.resize(n);
    for(int i = 0; i < n; ++i)
    {
        pr[i] = i;
    }
    vector<pair<int,int>> v;
    vector<string> ans;
    vector<  pair<string, pair<int,int>>> asks(k);
    for(int i = 0;i < k; ++i){
        string s;
        int a, b;
        cin >> s >> a >> b;
        a--;
        b--;
        asks.push_back({s,{a, b}});
    }
    reverse(asks.begin(), asks.end());
    for(int i = 0; i < k; ++i)
    {
       string s =asks[i].first;
       int a = asks[i].second.first;
       int b = asks[i].second.second;
        if(s == "cut")
        {
            if(get(a) != get(b))
            {
                unite(a, b);

            }
        }
        else
        {
            if(get(a) != get(b))
            {
                ans.push_back("NO");
            }
            else
            {
                ans.push_back("YES");
            }
        }

    }
    reverse(ans.begin(), ans.end());
    for(int i =0; i < ans.size(); ++i)
    {
        cout << ans[i] << endl;
    }
//    cout << ans;
    return 0;
}

