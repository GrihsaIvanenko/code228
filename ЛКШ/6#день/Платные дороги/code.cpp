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

bool cmp_chull(point a, point b){
    long long tmp = cros(a, b);
    if (tmp < 0) {
        return false;
    }
    else if (tmp > 0){
        return true;
    }
    return superlen(a) < superlen(b);
}

int up(point a){
    return (a.y > 0 || (a.y == 0 && a.x > 0));
}

bool less_comp(point a, point b){
    if (up(a) == up(b)){
        return cros(a, b) < 0;
    }
    return up(a) < up(b);
}

struct line{
    long long a, b, c;
    line(){}
    line(long long aa, long long bb, long long cc){
        a = aa;
        b = bb;
        c = cc;
    }
    point napr_to(){
        return point(-b, a);
    }
    point napr_back(){
        return point(b, -a);
    }
    point normal(){
        return point(a, b);
    }
};

vector<point> c_hull(vector<point> v){
    if (v.size() == 1){
        return v;
    }
    int n = v.size();
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
    sort(v.begin(), v.end(), cmp_chull);
    vector<point> hull;
    hull.push_back(v[0]);
    hull.push_back(v[1]);
    for (int i = 2; i < n; ++i){
        while (hull.size() > 1 && cros(v[i] - hull.back(), hull.back() - hull[hull.size() - 2]) >= 0){
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    for (int i = 0; i < hull.size(); ++i){
        hull[i] = hull[i] + base;
    }
    hull.push_back(v[0] + base);
    return hull;
}

long long get_C(int a, int b, point P){
    return -(P.x * a + P.y * b);
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<line> l;
    vector<point> metro;
    for (int i = 0; i < n; ++i){
        long long a, b, c;
        cin >> a >> b >> c;
        l.push_back(line(a, b, c));
    }
    for (int i = 0; i < m; ++i){
        long long a, b;
        cin >> a >> b;
        metro.push_back(point(a, b));
    }
    metro = c_hull(metro);
    vector<point> rebs;
    for (int i = 0; i < metro.size() - 1; ++i){
        rebs.push_back(metro[i + 1] - metro[i]);
    }
    sort(rebs.begin(), rebs.end(), less_comp);
    vector<int> ans_num;
    for (int i = 0; i < n; ++i){
        point a1 = l[i].napr_to();
        auto it1 = upper_bound(rebs.begin(), rebs.end(), a1, less_comp);
        a1 = l[i].napr_back();
        auto it2 = upper_bound(rebs.begin(), rebs.end(), a1, less_comp);
        int pos1 = it1 - rebs.begin(), pos2 = it2 - rebs.begin();
        pos1 = rebs.size() - pos1, pos2 = rebs.size() - pos2;
        long long C1 = get_C(l[i].a, l[i].b, metro[pos1]), C2 = get_C(l[i].a, l[i].b, metro[pos2]);
        if (l[i].c >= min(C1, C2) && l[i].c <= max(C1, C2)){
            ans_num.push_back(i + 1);
        }
    }
    cout << ans_num.size() << endl;
    for (auto x : ans_num){
        cout << x << " ";
    }
}

int main(){
    solve();
    return 0;
}
