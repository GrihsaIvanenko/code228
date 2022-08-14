#include  <bits/stdc++.h>

using namespace std;

int pows = 1;

void f(int x, vector<pair<int, pair<int,int>>> &v){
    if(v[x].first == -1)f(v[x].second.second, v);
    else{
        return;
    }
    v[x].first = v[v[x].second.second ].first + 1;
}

int gen(int s, int h, vector<vector<int>>&lol){
    if(h > pows){
        return 0;
    }
    short int pos = 0;
    while(h != 0){
        if(h % 2){
            s = lol[s][pos];
        }
        pos++;
        h = h>>1;
    }
    return s;
}

int main(){
    //freopen("moscow.out", "w", stdout);
    freopen("moscow.in", "r", stdin);
    freopen("moscow.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int,int>>> v(n);
    v[0] = {0,{0, 0}};
    int maxd = 0;
    for(int i = 1; i < n; ++i){
        v[i].first = -1;
        cin >> v[i].second.second;
        v[i].second.first = i;
    }
    for(int i = 1; i < n; ++i){
        if(v[i].first == -1)f(i, v);
        maxd = max(maxd, v[i].first);
    }
    sort(v.begin(), v.end());
    int size = 1;
    while(pows < maxd){
        size++;
        pows = pows << 1;
    }
    vector<vector<int>> anc(n, vector<int> (size));
    for(int i = 0; i < n; ++i){
        anc[v[i].second.first ][0] = v[i].second.second;
    }
    for(int i = 1; i < size; ++i){
        for(int j = 0; j < n; ++j){
            anc[ v[j].second.first ][i] = anc[anc[v[j].second.first ][i - 1] ][i - 1];
        }
    }
    v.clear();
    long long a[m * 2 + 1];
    long long x, y, z;
    cin >> a[1] >> a[2] >> x >> y >> z;
    for(int i = 3; i < 2 * m + 1; ++i){
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }
    long long ans = 0;
    ans = gen(a[1], a[2], anc);
    long long last = ans;
    for(int i = 2; i <= m; ++i){
        last = gen((a[i * 2 - 1] + last) % n ,a[i * 2], anc);
        ans += last;
    }
    cout << ans << endl;
    return 0;
}
