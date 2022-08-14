#include <bits/stdc++.h>

using namespace std;


const long double eps = 1e-5;

bool equal(long double a, long double b){return a - b > -eps;}

struct point{
    long double x, y;
    point(){}
    point(int x_, int y_){x = x_; y = y_;}
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

int main(){freopen("goat3.in", "r", stdin);freopen("goat3.out", "w", stdout);

    long double d, e, f, g, h, i, j;
    cin >> d >> e >> f >> g >> h >> i >> j;
    point a = point(d, e), b = point(f, g), c = point(h, i);
    line l = line(a, b);
    line m = line(-l.b, l.a, l.b * c.x - l.a * c.y);
    point lox = intersection(l, m);//cout << lox.x << " " << lox.y << endl;
    cout.precision(7);
    if(belong(a, b, lox))cout << fixed << max((long double)0.0, sqrt((lox.x - c.x) * (lox.x - c.x) + (lox.y - c.y) * (lox.y - c.y)) - j) << endl;
    else cout << fixed << max((long double)0.0,min(len(a - c), len(b - c)) - j) << endl;
    cout << fixed << max((long double)0.0,max(len(a - c), len(b - c)) - j) << endl;return 0;
}
