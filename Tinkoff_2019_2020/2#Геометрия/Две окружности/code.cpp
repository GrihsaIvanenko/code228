#include <bits/stdc++.h>

using namespace std;

#define ld long double

struct Point {
    ld x, y;
    Point () {}
    Point (ld a, ld b) {
        x = a;
        y = b;
    }
};

ld dust (Point A) {
    return sqrt(A.x * A.x + A.y * A.y);
}

Point operator - (Point a, Point b) {
    return Point (a.x - b.x, a.y - b.y);
}

Point operator + (Point a, Point b) {
    return Point (a.x + b.x, a.y + b.y);
}

struct circle{
    ld R;
    Point centre;
    circle (Point p, ld RR) {
        R = RR;
        centre = p;
    }
};

const ld eps = 1e-7;

bool eqw(ld a, ld b) {
    return fabs(a - b) < eps;
}

bool operator == (Point a, Point b) {
    return eqw(a.x, b.x) && eqw(a.y, b.y);
}

bool les(ld a, ld b) {
    return (a - b) < eps;
}

Point go(Point from, Point to, ld  dist) {
    return Point (from.x + to.x * dist / dust(to), from.y + to.y * dist / dust(to));
}

vector<Point> intersect(circle A, circle B) {
    vector<Point> ans;
    if (eqw(A.R, B.R) && A.centre == B.centre) {
        ans.push_back(Point(0.0, 0.0));
        ans.push_back(Point(0.0, 0.0));
        ans.push_back(Point(0.0, 0.0));
        return ans;
    }
    if (les(dust(A.centre - B.centre) + min(A.R, B.R) + eps + eps + eps + eps, max(A.R, B.R)) ) {
        return ans;
    }
    if (eqw(dust(A.centre - B.centre), A.R + B.R)) {
        ans.push_back(go(A.centre, B.centre - A.centre, A.R));
        return ans;
    } else if (eqw(dust(A.centre - B.centre) + min(A.R, B.R), max(A.R, B.R))) {
        ans.push_back(go(A.centre, B.centre - A.centre, A.R));
        return ans;
    }else if (les(dust(A.centre - B.centre), A.R + B.R)) {
        Point C = B.centre - A.centre;
        ld X = (dust(C) * dust(C) + A.R * A.R - B.R * B.R) / (ld)2.0 / dust(C);
        ld Y = sqrt(A.R * A.R - X * X);
        ans.push_back(go(go(A.centre, C, X), Point(-C.y, C.x), Y));
        ans.push_back(go(go(A.centre, C, X), Point(C.y, -C.x), Y));
        return ans;
    }
    return ans;
}

int main () {
    ld R1, R2;
    Point A, B;
    cin >> A.x >> A.y >> R1 >> B.x >> B.y >> R2;
    circle a = circle(A, R1), b = circle(B, R2);
    vector<Point> p = intersect(a, b);
    if (p.size() == 3) {
        cout << p.size() << '\n';
        return 0;
    }
    cout << p.size() << '\n';
    cout.precision(10);
    for (auto x : p) {
        cout << fixed << x.x << ' ' << x.y << '\n';
    }
    return 0;
}
