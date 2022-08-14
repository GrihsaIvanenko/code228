#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000007;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >>  m;
    int to = n * m, sx, tmp  = 0;
    int mp[to], used[to], number[to];
    char x;
    for(int i = 0; i < to; ++i){
        used[i] = 0;
        cin >> x;
        if(x == '.')mp[i] = INF;
        else if(x == 'S')mp[i] = 1;
        else {
                mp[i] = 0;
                sx = i;
        }
    }
    vector<int> coor;
    deque<int> q;
    q.push_front(sx);
    while(!q.empty()){
        int it = q.front();
        q.pop_front();
        if(used[it] == 1)
            continue;
        if(mp[it] == 0){
            coor.push_back(it);
            deque<int> q1;
            q1.push_front(it);
            while(!q1.empty()){
                int it1 = q1.front();
                q1.pop_front();
                if(used[it1] == 1)
                    continue;
                used[it1] = 1;
                number[it1] = tmp;
                if(it1 % m != m - 1 && !used[it1 + 1] && mp[it1 + 1] == 0)
                    q1.push_back(it1 + 1);
                else if(it1 % m != m - 1 && !used[it1 + 1])
                    q.push_back(it1 + 1);
                if(it1 % m != 0 && !used[it1 - 1] && mp[it1 - 1] == 0)
                    q1.push_back(it1 - 1);
                else if(it1 % m != 0 && !used[it1 - 1])
                    q.push_back(it1 - 1);
                if(it1 / m != n - 1 && !used[it1 + m] && mp[it1 + m] == 0)
                    q1.push_back(it1 + m);
                else if(it1 / m != n - 1 && !used[it1 + m])
                    q.push_back(it1 + m);
                if(it1 / m != 0 && !used[it1 - m] && mp[it1 - m] == 0)
                    q1.push_back(it1 - m);
                else if(it1 / m != 0 && !used[it1 - m])
                    q.push_back(it1 - m);
            }
            ++tmp;
        }
        else{
            used[it] = 1;
            number[it] = INF;
            if(it % m != m - 1 && !used[it + 1])
                q.push_back(it + 1);
            if(it % m != 0 && !used[it - 1])
                q.push_back(it - 1);
            if(it / m != n - 1 && !used[it + m])
                q.push_back(it + m);
            if(it / m != 0 && !used[it - m])
                q.push_back(it - m);
        }
    }
    int islands = coor.size();
    int dust[islands][islands];
    deque<pair<int, int>> q1;
    for(int i = 0; i < islands; ++i){
        q1.push_back({coor[i], 0});
        while(!q1.empty()){
            int it = q1.front().first, cost = q1.front().second;
            q1.pop_front();
            if(used[it] == i + 2)
                continue;
            used[it]= i + 2;
            if(mp[it] == 0)
                dust[i][number[it]] = cost;
            if(it % m != m  - 1 && used[it + 1] != i + 2 && mp[it + 1] == 0)
                q1.push_front({it + 1, cost});
            else if(it % m != m  - 1 && used[it + 1] != i + 2 && mp[it + 1] == 1)
                q1.push_back({it + 1, cost + 1});
            if(it % m != 0 && used[it - 1] != i + 2 && mp[it - 1] == 0)
                q1.push_front({it - 1, cost});
            else if(it % m != 0 && used[it - 1] != i + 2 && mp[it - 1] == 1)
                q1.push_back({it - 1, cost + 1});
            if(it / m != n - 1 && used[it + m] != i + 2 && mp[it + m] == 0)
                q1.push_front({it + m, cost});
            else if(it / m != n - 1 && used[it + m] != i + 2 && mp[it + m] == 1)
                q1.push_back({it + m, cost + 1});
            if(it / m != 0 && used[it - m] != i + 2 && mp[it - m] == 0)
                q1.push_front({it - m, cost});
            else if(it / m != 0 && used[it - m] != i + 2 && mp[it - m] == 1)
                q1.push_back({it - m, cost + 1});
        }
    }
    int mmask = 1<<islands;
    int dp[islands][mmask];
    for(int i = 0; i < islands; ++i){
        for(int j = 0; j < (1<<islands); ++j)
            dp[i][j] = INF;
        dp[i][1<<i] = 0;
    }
    for(int mask = 3; mask < mmask; ++mask){
        for(int i = 0; i < islands; ++i){
            if(mask&(1<<i)){
                for(int j = 0; j < islands; ++j){
                    if(i != j)
                        dp[i][mask] = min(dp[i][mask], dp[j][mask - (1<<i)] + dust[j][i]);
                }
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < islands; ++i)
        ans = min(ans, dp[i][mmask - 1]);
    cout << ans << '\n';
    return 0;
}
