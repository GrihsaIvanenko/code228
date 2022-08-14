#include <bits/stdc++.h>

using namespace std;

using ld = long double;

int TOCHNOST = 10;

const ld EPS = 1e-6;

struct Point {
    ld x, y;
    Point() {}
    Point(ld xx, ld yy) {
        x = xx;
        y = yy;
    }
    void MULT(ld z) {
        x *= z;
        y *= z;
    }
    ld len() {
        return sqrt(x * x + y * y);
    }
    void read() {
        cin >> x >> y;
    }
    void print() {
        cout.precision(TOCHNOST);
        cout << fixed << x << ' ' << y;
    }
    void println() {
        print();
        cout << '\n';
    }
};

struct Circle {
    Point C;
    ld R;
    Circle() {}
    Circle(Point CC, ld RR) {
        C = CC;
        R = RR;
    }
};

struct Line {
    ld a, b, c;
    Line() {}
    Line(ld aa, ld bb, ld cc) {
        a = aa;
        b = bb;
        c = cc;
    }
    Line(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
};

bool eq(ld a, ld b) {
    return fabs(a - b) < EPS;
}

ld cross(Point A, Point B) {
    return A.x * B.y - B.x * A.y;
}

bool gcoline(Point a, Point b) {
    return eq(cross(a, b), 0.0);
}

bool collinear(Line a, Line b) {
    Point A = Point(a.a, a.b);
    Point B = Point(b.a, b.b);
    return gcoline(A, B);
}

Point intersect(Line a, Line b) {
   if (collinear(a, b)) {
        while (true) {
            cout << "TRATATA! TRATATA! MI VEZEM S SOBOY KOTA!!!\n";
        }
   }
   return Point((b.c * a.b - a.c * b.b) / (b.b * a.a - a.b * b.a), (a.c * b.a - b.c * a.a) / (b.b * a.a - a.b * b.a));
}

Point operator -(Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y);
}

Point operator +(Point A, Point B) {
    return Point(A.x + B.x, A.y + B.y);
}

Line bisector(Point A, Point B, Point C) {
    A = A - B;
    C = C - B;
    ld x1 = A.len(), x2 = C.len();
    Point D = C - A;
    D.MULT(x1 / (x1 + x2));
    A = A + D;
    A = A + B;
    return Line(B, A);
}

ld dust_Point_Line (Point A, Line l) {
    return fabs(A.x * l.a + A.y * l.b + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

struct Triangle {
    Point A, B, C;
    Triangle() {}
    Triangle(Point A1, Point B1, Point C1) {
        A = A1;
        B = B1;
        C = C1;
    }
    void read() {
        A.read();
        B.read();
        C.read();
    }
    Circle vpis() {
        Circle res;
        res.C = intersect(bisector(A, B, C), bisector(A, C, B));
        Line AB = Line(A, B);
        res.R = dust_Point_Line(res.C, AB);
        return res;
    }
};

int main() {
    freopen("goat4.in", "r", stdin);
    freopen("goat4.out", "w", stdout);
    Triangle ABC;
    ABC.read();
    Circle ans = ABC.vpis();
    ans.C.println();
    return 0;
}
