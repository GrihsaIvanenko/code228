#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
    point(){}
    point(long long xx, long long yy) {
        x = xx;
        y = yy;
    }
};

point operator +(point a, point b){
    return point(a.x + b.x, a.y + b.y);
}

long long cros(point a, point b) {
    return a.x * b.y - b.x * a.y;
}

point operator -(point a, point b){
    return point(a.x - b.x, a.y - b.y);
}

long long superlen(point a){
    return a.x * a.x + a.y * a.y;
}

bool cmp(point a, point b){
    if (cros(a, b) != 0){
        return cros(a, b) > 0;
    }
    return superlen(a) < superlen(b);
}

vector<point> c_hull(vector<point> v) {
    if (v.size() == 1) {
        return v;
    }
    int n = v.size();
    int it = 0;
    for (int i = 1; i < v.size(); ++i){
        if (v[it].y > v[i].y || (v[it].y == v[i].y && v[it].x > v[i].x)){
            it = i;
        }
    }
    point base = v[it];
    for (int i = 0; i < n; ++i) {
        v[i] = v[i] - base;
    }
    sort(v.begin(), v.end(), cmp);
    vector<point> hull;
    hull.push_back(v[0]);
    hull.push_back(v[1]);
    for (int i = 2; i < n; ++i){
        while (hull.size() > 1 && cros(v[i] - hull.back(), hull.back() - hull[hull.size() - 2]) >= 0){
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    hull.push_back(v[0]);
    for (int i = 0; i < hull.size(); ++i){
        hull[i] = hull[i] + base;
    }
    return hull;
}

void solve(){
    int n;
    cin >> n;
    vector<point> v;
    for (int i = 0; i < n; ++i){
        long long a, b;
        cin >> a >> b;
        v.push_back(point(a, b));
    }
    v = c_hull(v);
    cout.precision(13);
    if (v.size() == 1){
        cout << fixed << 0;
        return;
    }
    if (v.size() == 3){
        cout << fixed << sqrt(superlen(v[1] - v[0]));
        return;
    }
    n = v.size();
    for (int i = 1; i < n; ++i){
        v.push_back(v[i]);
    }
    long long ans = 0;
    int it = 2;
    for (int i = 1; i <= n; ++i){
        while (cros(v[i] - v[i - 1], v[it - 1] - v[it]) <= 0){
            ans = max(ans, superlen(v[it] - v[i]));
            ++it;
        }
        --it;
    }
    cout << fixed << sqrt((long double)ans);
}

int main(){
    solve();
    return 0;
}
