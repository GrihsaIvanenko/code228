#include <bits/stdc++.h>

using namespace std;


const long double eps = 1e-5;

bool equal(long double a, long double b){return a - b > -eps;}

struct point{
    long double x, y;
    point(){}
    point(double x_, long double y_){x = x_; y = y_;}
};

point operator +(point a, point b){return point(a.x + b.x, a.y + b.y);}
point operator -(point a, point b){return point(a.x - b.x, a.y - b.y);}
long double len(point a){//cout << a.x << " " << a.y << endl;
    return sqrt(a.x * a.x + a.y * a.y);}
long double scal(point a, point b){return a.x * a.x + a.y * a.y;}
long double vect(point a, point b){return a.x * b.y - a.y * b.x;}
point operator /(point a, double x){return point(a.x / x, a.y / x);}
point operator *(point a, double x){return point(a.x * x, a.y * x);}
point rotate(point a){return point(-a.y, a.x);}

struct line{
    long double a, b, c;
    line(){}
    line(point A, point B){
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    line(long double a1, long double b1, long double c1){a = a1; b = b1; c = c1;}
};
bool parallel(line a, line b){equal(a.a * b.b - b.a * a.b, 0.0);}

point intersection(line a, line b){point lox;lox.x = (long double)(a.b * b.c - b.b * a.c) / (long double)(a.a * b.b - b.a * a.b);
lox.y =  - (long double)(a.a * b.c - b.a * a.c) / (long double)(a.a * b.b - b.a * a.b);//cout << x1 << " " << y1 << endl;
    return lox;
    }

bool belong(point st, point finish, point who){
    return equal(who.x, min(st.x, finish.x)) && equal(max(st.x, finish.x), who.x) && equal(who.y, min(st.y, finish.y)) && equal(max(st.y, finish.y), who.y);
}

int main(){//freopen("point.in", "r", stdin);freopen("intersec1.out", "w", stdout);
    int n;
    cin >> n;
    vector<point> v(n);
    for(int i = 0; i < n; ++i){
        long double x, y;
        cin >> x >> y;
        v[i] = point(x, y);
    }
    long double ans = 0.0;
    for(int i = 2; i < n; ++i){
        ans += vect(v[i - 1] - v[0], v[i] - v[0]);
    }
    cout << abs(ans) / 2.0<< endl;
    return 0;
}
