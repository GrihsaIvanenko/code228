#include <bits/stdc++.h>

using namespace std;

#define ll long long

#define ld long double

struct point{
    ld x, y;
    point(){}
    point(ll x_, ll y_){
        x = x_;
        y = y_;
    }
};

ld vec(point a, point b){
    return a.x * b.y - a.y * b.x;
}

ld scal(point a, point b){
    return a.x * b.x + a.y * b.y;
}

ld len(point a){
    return sqrt(a.x * a.x + a.y * a.y);
}

point operator -(point a, point b){
        return point(a.x - b.x, a.y - b.y);
}

point operator +(point a, point b){
    return point(a.x + b.x, a.y + b.y);
}

struct line{
    ld a, b, c;
    line(){}
    line(ld a_, ld b_, ld c_){
        a = a_;
        b = b_;
        c = c_;
    }
    line(point a1, point b1){
        point c1;
        c1.x = b1.x - a1.x;
        c1.y = b1.y - a1.y;
        //cout << c1.x << " " << c1.y << endl;
        a = -c1.y;
        b = c1.x;
        c = -(a * a1.x) -(b * a1.y);
    }
};


int main(){
    freopen("bisector.in", "r", stdin);
    freopen("bisector.out", "w", stdout);
    ld a, b, c, d, e, f;
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> a >> b >> c >> d >> e >> f;
    if(a == c && b == d)return 0;
    if(a == e && b == f)return 0;
    if(c == e && d == f)return 0;
    point A(a, b), B(c, d), C(e, f);
    point D(a, b), E(c, d), F(e, f);
    //swap(A, B);
    B = B - A;
    C = C - A;
    ld lena = len(B);
    B.x /= lena;
    B.y /= lena;
   // A.x *= lena;
    //A.y *= lena;
    lena = len(C);
    C.x /= lena;
    C.y /= lena;
    //A.x *= lena;
   // A.y *= lena;
    D = B + C;
    if(fabs(D.x - 0.0) < 1e-5 && fabs(D.y - 0.0) < 1e-5){
        line AAA = line(E, F);
        swap(AAA.a, AAA.b);
        AAA.a = -AAA.a;
        AAA.c = -(D.x * AAA.a + D.y * AAA.b);
        cout.precision(10);
        cout << fixed << AAA.a << " " << AAA.b << " " << AAA.c << endl;
        return 0;
    }
    point lox;
    lox.x = A.x + B.x + C.x;
    lox.y = A.y + B.y + C.y;
    //cout.precision(10);
    line AAA(A, lox);
    //lena = len(point(AAA.a, AAA.b));
    //AAA.a /= lena;
    //AAA.b /= lena;
    //AAA.c /= lena;
    cout.precision(10);
    cout << fixed << AAA.a << " " << AAA.b << " " << AAA.c << endl;
    return 0;
}
