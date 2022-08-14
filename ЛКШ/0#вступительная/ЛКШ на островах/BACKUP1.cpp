#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9+7;

int gcd(int a, int b){
    if(b == 0)return a;
    return gcd(b, a % b);
}

bool simple[100000001];

int main(){
    int ans = 0;
    for(int i = 2; i <= 10000000; ++i){
        simple[i] = 1;
        for(int j = 2;j * j <= i; ++j){
            if(i % j == 0){
                simple[i] = false;
                break;
            }
        }
    }
    for(int i = 3; i <= 10000000; ++i){
        bool good = true;
        for(int m = 2; m < i; ++m){
            if(gcd(i, m) == 1)
                if(!simple[m]){
                    good = false;
                    break;
                }
        }
        if(good){
            ++ans;
            cout << i<< endl;
        }
    }
    cout << ans << " ans" << endl;
    return 0;
//    cout << ans << endl;
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
    vector<vector<int>> dust(coor.size(), vector<int>(coor.size(), INF ));
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
     for(auto x : number){
        for(auto y : x){
            cout<< y << " ";
        }
        cout << endl;
    }
    cout << "number" << endl << endl;
    for(auto x : dust){
        for(auto y : x){
            cout<< y << " ";
        }
        cout << endl;
    }
    cout << "dust" << endl;
    for(int i = 0; i < coor.size(); ++i){
        dust[i][i] = INF;
    }
    bool solved = 0;
    vector<vector<int>> good_dust(coor.size(), vector<int>(coor.size()));
    for(int i = 0; i < coor.size(); ++i)
        good_dust[i] = dust[i];
    vector<pair<int,int>> answer_reb;
    while(answer_reb.size() < coor.size()){
        vector<int> hor(dust.size()), stolb(dust.size());
        for(int i = 0; i < dust.size(); ++i){
            int mind = INF;
            for(int j = 0; j < dust.size(); ++j){
                mind = min(mind, dust[i][j]);
            }
            if(mind == INF)hor[i] = -mind;
            else hor[i] = mind;
            for(int j = 0; j < dust.size(); ++j){
                if(dust[i][j] != INF){
                        dust[i][j] -= mind;
                        //cout << dust[i][j] << " ";
                }
                //else cout << "- ";
            }
            //cout << hor[i] << endl;
        }
        for(int j = 0; j < dust.size(); ++j){
            int mind = INF;
            for(int i = 0; i < dust.size(); ++i){
                mind = min(mind, dust[i][j]);
            }
            if(mind == INF)stolb[j] = -mind;
            else stolb[j] = mind;
            for(int i = 0; i < dust.size(); ++i){
                if(dust[i][j] != INF){
                        dust[i][j] -= mind;
                }
            }
        }
        for(int i = 0; i < dust.size();++i){
            for(int j = 0; j < dust.size(); ++j){
                if(dust[i][j] != INF){
                    cout << dust[i][j] << " ";
                }
                else   cout << "- ";
            }
            cout << hor[i] << endl;
        }
        for(int i = 0; i < dust.size(); ++i){
            cout << stolb[i] << " ";
        }
        cout << endl;
        vector<pair<int, pair<int,int>>> p;
        for(int i = 0; i < dust.size(); ++i){
            for(int j = 0; j < dust.size(); ++j){
                if(dust[i][j] == 0){
                    p.push_back({hor[i] + stolb[j], {i, j} });
                }
            }
        }
        sort(p.begin(), p.end());
        answer_reb.push_back(p.back().second);
        dust[answer_reb.back().second][answer_reb.back().first] = INF;
        dust.erase(dust.begin() + answer_reb.back().first);
        for(int i = 0; i < dust.size(); ++i){
            dust[i].erase(dust[i].begin() + answer_reb.back().second);
        }
        cout << p.back().second.first << " " << p.back().second.second << endl;

    }
    int sum = 0, maxreb = 0;
    for(auto x : answer_reb){
        cout << x.first << " ans " << x.second << endl;
    }
    for(int i = 0; i < dust.size(); ++i){
        sum += good_dust[answer_reb[i].first ][answer_reb[i].second ];
        maxreb = max(maxreb, good_dust[answer_reb[i].first ][answer_reb[i].second ]);
    }
    cout << sum - maxreb << '\n' << endl;
    return 0;
}
