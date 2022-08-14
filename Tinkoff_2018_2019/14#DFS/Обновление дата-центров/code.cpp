#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v, rev, cond_v, cond_rev;
vector<int> top_sort, used, ans, trunda;
map<int, int> to;
map<int, vector<int>> mm;

bool good_ = true;

int ch_comp = 0, it = 0;

void dfs_with_top_sort(int x){
    used[x] = true;
    for(int i = 0; i < v[x].size(); ++i){
        if(!used[v[x][i]]){
            dfs_with_top_sort(v[x][i]);
        }
    }
    top_sort.push_back(x);
}

void dfs_condensator(int x){
    used[x] = 1;
    trunda.push_back(x);
    to[x] = ch_comp;
     mm[ch_comp].push_back(x);
    for(auto y : rev[x]){
        if(used[y] < 1){
            dfs_condensator(y);
        }
        else if(used[y] == 2){
            cond_v[to[y]].push_back(ch_comp);
            cond_rev[ch_comp].push_back(to[y]);
        }
    }
}

void dfs(int x){

    used[x] = 1;
    for(auto y : cond_v[x]){
        if(used[y] == 0){
            dfs(y);
            return;
        }
        return;
    }
        it = x;
        good_ = true;
}

int main(){
    int n, m, h;
    cin >> n >> m >> h;
    used.assign(n, 0);
    v.resize(n);
    vector<set<int>> ban(n);
    rev.resize(n);
    cond_rev.resize(n);
    cond_v.resize(n);
    vector<int> time(n);
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        time[i] = x;
    }
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int a1 = time[a], b1 = time[b];
        if(a1 + 1 == b1 || (b1 == 0 && a1 == h - 1)){
            if(ban[a].find(b) == ban[a].end()){
                ban[a].insert(b);
                v[a].push_back(b);
                rev[b].push_back(a);
            }
        }
    if(b1 + 1 == a1 || (a1 == 0 && b1 == h - 1)){
            if(ban[b].find(a) == ban[b].end()){
                ban[b].insert(a);
                v[b].push_back(a);
                rev[a].push_back(b);
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(used[i] == 0){
            dfs_with_top_sort(i);
        }
    }
    used.assign(n, 0);
    for(int i = n - 1; i > -1; --i){
        if(used[top_sort[i]] == 0){
            dfs_condensator(top_sort[i]);
            ch_comp++;
            for(int j = 0; j < trunda.size(); ++j){
                used[trunda[j]] = 2;
            }
            trunda.clear();
        }
    }
    used.assign(n, 0);
    ans.clear();
    for(int i = 0; i < ch_comp; ++i){
        good_ = false;
        if(used[i] == 0){
            dfs(i);
        }
        if(good_){
            ans.push_back(it);
        }
    }
    int ind = 0;
    int min_size = 1000000000;
    for(int i = 0; i < ans.size(); ++i){
        if(mm[ans[i]].size() < min_size){
            ind = i;
            min_size = mm[ans[i]].size();
        }
    }
    cout << mm[ans[ind]].size() << endl;
    for(auto x : mm[ans[ind]]){
        cout << x + 1 << " ";
    }
    cout << endl;
    return 0;
}
