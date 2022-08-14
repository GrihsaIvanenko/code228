#include <bits/stdc++.h>

using namespace std;

struct point{
    long long x, y;
    point(int xx, int yy){
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
    long long tmp = cros(a, b);
    if (tmp < 0) {
        return false;
    }
    else if (tmp > 0){
        return true;
    }
    return superlen(a) < superlen(b);
}

void solve(){
    int n;
    cin >> n;
    vector<point> v(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        v[i] = point(a, b);
    }
    int it = 0;
    for (int i = 1; i < n; ++i) {
        if (v[it].y > v[i].y) {
            it = i;
        }
        else if (v[it].y == v[i].y && v[it].x > v[i].x) {
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
    cout << hull.size() << endl;
    for (auto z : hull){
        point t = z + base;
        cout << t.x << " " << t.y << endl;
    }
    hull.push_back(v[0]);
    long long ans = 0;
    for (int i = 0; i < hull.size(); ++i){
        ans += cros(hull[i], hull[i + 1]);
    }
    if (ans < 0){
        ans = -ans;
    }
    cout << (ans>>1) << '.' << (ans % 2) * 5 << endl;
}

int main(){
    solve();
    return 0;
}
