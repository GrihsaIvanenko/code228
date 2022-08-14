#include <bits/stdc++.h>

using namespace std;

struct point{
    long long x, y;
    point(long long xx, long long yy){
        x = xx;
        y = yy;
    }
    point(){}
};

bool operator ==(point a, point b){
    return (a.x == b.x && a.y == b.y);
}

point operator -(point a, point b){
    return point(a.x - b.x, a.y - b.y);
}

point operator +(point a, point b){
    return point(a.x + b.x, a.y + b.y);
}

long long cros(point a, point b){
    return a.x * b.y - b.x * a.y;
}

long long dot(point a, point b){
    return a.x * b.x + a.y * b.y;
}

long long superlen(point a){
    return a.x * a.x + a.y * a.y;
}

bool cmp(point a, point b){
    return cros(a, b) > 0;
}

bool in(point t, vector<point> &v){
    if (cros(v[0], t) >= 0 && cros(t, v.back()) >= 0){
        auto pose = upper_bound(v.begin(), v.end(), t, cmp);
        int pos = pose - v.begin();
        if (pos == v.size()){
            return superlen(v[pos - 1]) >= superlen(t);
        }
        return (cros(v[pos] - v[pos - 1], t - v[pos - 1]) >= 0);
    }
    return false;
}

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<point> polygon(n), v;
    int it = 0;
    for (int i = 0; i < n; ++i){
        int a, b;
        cin >> a >> b;
        polygon[i] = point(a, b);
        if (polygon[it].y > polygon[i].y || (polygon[it].y == polygon[i].y && polygon[it].x > polygon[i].x)){
            it = i;
        }
    }
    point base = polygon[it];
    for (int i = it + 1; i < n; ++i){
        v.push_back(polygon[i] - base);
    }
    for (int i = 0; i < it; ++i){
        v.push_back(polygon[i] - base);
    }
    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        point t = point(a, b);
        t = t - base;
        if (in(t, v)){
            --k;
        }
    }
    if (k <= 0){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
}

int main(){
    solve();
    return 0;
}
