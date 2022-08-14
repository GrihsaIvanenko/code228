#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9+7;

int sizes = 16;
int mmask = 1<<sizes;
int dp[1<<16][16];
int dust[16][16];

inline int chitu(int mask, int i){
    if(dp[mask][i] == INF)
        for(int j = 0; j < 16; ++j)
            if(mask & (1<<j) && j != i)
                dp[mask][i]= min(dp[mask][i], chitu(mask ^ (1<<i), j) + dust[j][i]);
    return  dp[mask][i];
}


int main(){
    array<int, 1, 100> x;
    for(auto y : x)cout << y << endl;
    mt19937 gen(0);
   // while(gen())cout << gen;
    return 0;
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 16; ++j)
            dust[i][j] = INF;
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, startx, starty;
    cin >> n >> m;
    vector<vector<int>> mm(n, vector<int>(m)),
     used(n, vector<int>(m)), number(n, vector<int>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            char x;
            cin >> x;
            if(x == 'X'){
                startx = i;
                starty = j;
                mm[i][j] = 0;
            }
            else if(x == 'S'){
                mm[i][j] = 1;
            }
            else
                mm[i][j] = INF;
        }
    }
    /*for(auto x : mm){
        for(auto y : x){
            if(y != INF)cout << y << " ";
            else cout << "3 ";
        }
        cout << endl;
    }
    cout << "mm" << endl;*/
    vector<pair<int,int>> coor;
    if(true){
        deque<pair<int,int>> q;
        q.push_front({startx, starty});
        while(!q.empty()){
            int x1 = q.front().first,
            y1 = q.front().second;
            q.pop_front();
            if(used[x1][y1])continue;
            used[x1][y1] = 1;
            if(mm[x1][y1] == 0){
                coor.push_back({x1, y1});
                deque<pair<int,int>> q1;
                q1.push_front({x1, y1});
                while(!q1.empty()){
                    int x = q1.front().first,
                        y = q1.front().second;
                    q1.pop_front();
                    used[x][y] = 1;
                    number[x][y] = coor.size();
                    if(x != n - 1 && !used[x + 1][y] && mm[x + 1][y] == 1)
                        q.push_back({x + 1, y});
                    else if(x != n - 1 && !used[x + 1][y] && mm[x + 1][y] == 0)
                        q1.push_back({x + 1, y});

                    if(y != m - 1 && !used[x][y + 1] && mm[x][y + 1] == 1)
                        q.push_back({x, y + 1});
                    else if(y != m - 1 && !used[x][y + 1] && mm[x][y + 1] == 0)
                        q1.push_back({x, y + 1});

                    if(x != 0 && !used[x - 1][y] && mm[x - 1][y] == 1)
                        q.push_back({x - 1, y});
                    else if(x != 0 && !used[x - 1][y] && mm[x - 1][y] == 0)
                        q1.push_back({x - 1, y});

                    if(y != 0 && !used[x][y - 1] && mm[x][y - 1] == 1)
                        q.push_back({x, y - 1});
                    else if(y != 0 && !used[x][y - 1] && mm[x][y - 1] == 0)
                        q1.push_back({x, y - 1});
                }
            }
            if(x1 != n - 1 && !used[x1 + 1][y1] && mm[x1 + 1][y1] != INF)
                q.push_back({x1 + 1, y1});
            if(y1 != m - 1 && !used[x1][y1 + 1] && mm[x1][y1 + 1] != INF)
                q.push_back({x1, y1 + 1});
            if(x1 != 0 && !used[x1 - 1][y1] && mm[x1 - 1][y1] != INF)
                q.push_back({x1 - 1, y1});
            if(y1 != 0 && !used[x1][y1 - 1] && mm[x1][y1 - 1] != INF)
                q.push_back({x1, y1 - 1});
        }
    }
    //if(coor.size() == 14)return 1;
    //if(coor.size() == 15)return 1;
    //if(coor.size() == 16)return 1;
   /* for(auto x : coor){
        cout << x.first << " " << x.second << endl;
    }
    cout << "coor" << endl;
    for(auto x : number){
        for(auto y : x){
            cout<< y << " ";
        }
        cout << endl;
    }
    cout << "number" << endl;*/

    for(int i = 0; i < coor.size(); ++i){
        deque<pair<int, pair<int,int>>> q;
        q.push_front({0, coor[i] });
        while(!q.empty()){
            int dist = q.front().first,
            x = q.front().second.first,
            y = q.front().second.second;
            q.pop_front();
            used[x][y] = i + 2;
            if(mm[x][y] == 0){
                dust[i][number[x][y] - 1] = dist;
            }
            if(x != n - 1 && mm[x + 1][y] == 0 && used[x + 1][y] == i + 1)
                q.push_front({dist, {x + 1, y} });
            else if(x != n - 1 && mm[x + 1][y] == 1 && used[x + 1][y] == i + 1)
                q.push_back({dist + 1, {x + 1, y} });
            if(y != m - 1 && mm[x][y + 1] == 0 && used[x][y + 1] == i + 1)
                q.push_front({dist, {x, y + 1} });
            else if(y != m - 1 && mm[x][y + 1] == 1 && used[x][y + 1] == i + 1)
                q.push_back({dist + 1, {x, y + 1} });
            if(x != 0 && mm[x - 1][y] == 0 && used[x - 1][y] == i + 1)
                q.push_front({dist, {x - 1, y} });
            else if(x != 0 && mm[x - 1][y] == 1 && used[x - 1][y] == i + 1)
                q.push_back({dist + 1, {x - 1, y} });
            if(y != 0 && mm[x][y - 1] == 0 && used[x][y - 1] == i + 1)
                q.push_front({dist, {x, y - 1} });
            else if(y != 0 && mm[x][y - 1] == 1 && used[x][y - 1] == i + 1)
                q.push_back({dist + 1, {x, y - 1} });
        }
    }
    /*for(auto x : dust){
        for(auto y : x){
            cout<< y << " ";
        }
        cout << endl;
    }
    cout << "dust" << endl;*/

    for(int i = 0; i < mmask; ++i)
        memset(dp[i], 21474836467, 16);
    for(int i = 0; i < sizes; ++i){
        dp[1<<i][i] = 0;
    }
    /*for(int i = 0; i < mmask; ++i){
        for(int j = 0; j < sizes; ++j){
            if(dp[i][j] != INF)cout << dp[i][j] << " ";
            else cout << "- ";
        }
        cout << endl;
    }*/
    int ans = INF;
    for(int i = 0; i < coor.size(); ++i)
        ans = min(chitu((1<<coor.size()) - 1, i), ans);
    cout << ans << '\n';
    return 0;
}
